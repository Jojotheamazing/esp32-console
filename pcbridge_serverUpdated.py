#!/usr/bin/env python3
"""
pcbridge_server.py  —  PC side of PCBridge
"""

import socket
import struct
import threading
import time
import io
import sys
import subprocess
import os

from PIL import Image, ImageDraw

try:
    import mss
    from PIL import Image
    import pyautogui
    import pydirectinput  # Swapped to pydirectinput for Minecraft compatibility
except ImportError:
    print("ERROR: pip install pillow mss pyautogui pydirectinput")
    sys.exit(1)

try:
    import pygetwindow as gw
    HAS_GW = True
except ImportError:
    HAS_GW = False
    print("[warn] pygetwindow not found — window targeting disabled")

# ── Settings ──────────────────────────────────────────────────
HOST          = '0.0.0.0'
PORT          = 5555
DISCOVERY_PORT = 4999
OUT_W         = 320
OUT_H         = 240
JPEG_QUALITY  = 70
TARGET_FPS    = 30

KNOWN_GAMES = {
    "Minecraft": r"C:\Program Files (x86)\Minecraft Launcher\MinecraftLauncher.exe",
    "Notepad":   r"C:\Windows\System32\notepad.exe",
}

# Global dictionary to map dynamically discovered game names to their paths/URLs
DYNAMIC_GAMES = {}

def refresh_game_list():
    """Scans the PC for installed Steam games, Start Menu shortcuts, and Desktop games."""
    global DYNAMIC_GAMES
    DYNAMIC_GAMES = {}
    
    # 1. Populate initial hardcoded defaults if they exist
    for name, path in KNOWN_GAMES.items():
        if os.path.exists(path):
            DYNAMIC_GAMES[name[:63]] = path

    # 2. Automatically discover Steam Games via local appmanifest files
    steam_paths = [
        r"C:\Program Files (x86)\Steam\steamapps",
        r"C:\Program Files\Steam\steamapps"
    ]
    for sp in steam_paths:
        if os.path.exists(sp):
            for file in os.listdir(sp):
                if file.endswith(".acf") and file.startswith("appmanifest_"):
                    try:
                        with open(os.path.join(sp, file), 'r', encoding='utf-8', errors='ignore') as f:
                            content = f.read()
                            appid, game_name = "", ""
                            for line in content.splitlines():
                                if '"appid"' in line:
                                    appid = line.split('"')[3]
                                if '"name"' in line:
                                    game_name = line.split('"')[3]
                            if appid and game_name:
                                # Truncate to 63 chars to fit ESP32 buffer safely
                                DYNAMIC_GAMES[game_name.strip()[:63]] = f"steam://rungameid/{appid}"
                    except:
                        pass

    # 3. Scan Start Menu and Desktop shortcuts for common game directories/keywords
    search_dirs = [
        os.path.expandvars(r"%ProgramData%\Microsoft\Windows\Start Menu\Programs"),
        os.path.expandvars(r"%AppData%\Microsoft\Windows\Start Menu\Programs"),
        os.path.expandvars(r"%USERPROFILE%\Desktop"),
        r"C:\XboxGames",
        r"C:\Program Files (x86)\Epic Games"
    ]
    
    # Keywords to filter out system apps, uninstaller utilities, and help files
    game_keywords = ["game", "minecraft", "gta", "cyberpunk", "steam", "epic", "ea", "ubisoft", "fortnite", "cod", "roblox", "valorant", "league", "witcher", "sims"]
    skip_keywords = ["uninstall", "help", "setup", "documentation", "config", "tool", "update", "crash"]

    for sdir in search_dirs:
        if not os.path.exists(sdir):
            continue
        for root, dirs, files in os.walk(sdir):
            for file in files:
                if file.endswith(".lnk"):
                    clean_name = file[:-4].strip()
                    if any(sk in clean_name.lower() for sk in skip_keywords):
                        continue
                    
                    # Target elements explicitly on the desktop, inside game folders, or matching a common game keyword
                    is_desktop = "Desktop" in root
                    is_game_folder = any(k in root.lower() for k in ["game", "epic", "steam", "xbox", "riot"])
                    matches_keyword = any(k in clean_name.lower() for k in game_keywords)

                    if is_desktop or is_game_folder or matches_keyword:
                        full_path = os.path.join(root, file)
                        DYNAMIC_GAMES[clean_name[:63]] = full_path

KEY_MAP = {
    10: 'w', 5: 's', 14: 'a', 0: 'd',
    6: 'space', 4: 'shift', 7: 'e', 9: 'f', 1: 'q', 2: 'tab',
}

MOUSE_MAP = {
    8: 'left', 3: 'right',
}

LOOK_SPEED = 12

# ── State & Velocity Engine Variables ─────────────────────────
# ── State & Velocity Engine Variables ─────────────────────────
pyautogui.PAUSE = 0
pydirectinput.PAUSE = 0
pydirectinput.FAILSAFE = False  # <-- ADD THIS LINE TO DISABLE THE CRASH

held_keys   = set()
held_mouse  = set()
stats       = {'frames': 0, 'bytes': 0, 'cmds': 0}

# Thread safe tracking for continuous joystick panning
current_rx = 0
current_ry = 0
joy_lock = threading.Lock()

# ── Discovery broadcast thread ────────────────────────────────
def broadcast_presence():
    sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    sock.setsockopt(socket.SOL_SOCKET, socket.SO_BROADCAST, 1)
    sock.settimeout(1)
    while True:
        try: sock.sendto(b"PCBRIDGE_SERVER", ("255.255.255.255", DISCOVERY_PORT))
        except: pass
        time.sleep(1)

# ── Window helpers ────────────────────────────────────────────
def get_window_region(title_substr):
    if not HAS_GW or not title_substr: return None
    try:
        wins = gw.getWindowsWithTitle(title_substr)
        if wins:
            w = wins[0]
            return {"left": w.left, "top": w.top, "width": w.width, "height": w.height}
    except: pass
    return None

def get_running_windows():
    if not HAS_GW: return []
    try: return [w.title for w in gw.getAllWindows() if w.title.strip()]
    except: return []

def launch_game(name):
    global DYNAMIC_GAMES
    path = DYNAMIC_GAMES.get(name) or KNOWN_GAMES.get(name)
    
    if path:
        try:
            print(f"[pcb] Direct launching: {name} via {path}")
            if sys.platform == "win32":
                # os.startfile mimics double-clicking the file/shortcut natively in Windows
                os.startfile(path)
            else:
                subprocess.Popen([path])
            time.sleep(3)  # Give the application time to open
            return True
        except Exception as e:
            print(f"[pcb] Failed to launch {name}: {e}")
    return False

# ── Input handlers ────────────────────────────────────────────
def handle_button(btn_id, is_down):
    stats['cmds'] += 1
    if btn_id in KEY_MAP:
        key = KEY_MAP[btn_id]
        if is_down and key not in held_keys:
            held_keys.add(key)
            pydirectinput.keyDown(key)
        elif not is_down and key in held_keys:
            held_keys.discard(key)
            pydirectinput.keyUp(key)
    elif btn_id in MOUSE_MAP:
        btn = MOUSE_MAP[btn_id]
        if is_down and btn not in held_mouse:
            held_mouse.add(btn)
            if btn == 'left': pydirectinput.mouseDown(button='left')
            else: pydirectinput.mouseDown(button='right')
        elif not is_down and btn in held_mouse:
            held_mouse.discard(btn)
            if btn == 'left': pydirectinput.mouseUp(button='left')
            else: pydirectinput.mouseUp(button='right')

def handle_joystick(lx, ly, rx, ry):
    global current_rx, current_ry
    with joy_lock:
        # Your ESP32 already handles deadzones and maps clean ranges (-100 to 100)
        # We just store the state here
        current_rx = rx
        current_ry = ry

def mouse_velocity_engine():
    """Background loop that moves the mouse continuously while a stick is pushed"""
    global current_rx, current_ry
    while True:
        with joy_lock:
            rx = current_rx
            ry = current_ry
        
        if rx != 0 or ry != 0:
            dx = int(rx * LOOK_SPEED / 100)
            dy = int(-ry * LOOK_SPEED / 100)  # Inverted Y axis correction (-)
            
            if dx != 0 or dy != 0:
                pydirectinput.moveRel(dx, dy, relative=True)
                
        # 10ms sleep loop runs at 100Hz for fluid camera tracking
        time.sleep(0.01)

def release_all():
    for key in list(held_keys):
        try: pydirectinput.keyUp(key)
        except: pass
    held_keys.clear()
    for btn in list(held_mouse):
        try:
            if btn == 'left': pydirectinput.mouseUp(button='left')
            else: pydirectinput.mouseUp(button='right')
        except: pass
    held_mouse.clear()

# ── Send helpers ──────────────────────────────────────────────
def send_frame(conn, jpeg_bytes):
    size = len(jpeg_bytes)
    conn.sendall(b'\xff' + struct.pack('<I', size) + jpeg_bytes)
    stats['frames'] += 1
    stats['bytes']  += size + 5

def send_game_list(conn, names):
    payload = bytes([len(names)])
    for n in names:
        payload += n.encode() + b'\x00'
    conn.sendall(bytes([0xA0]) + struct.pack('<H', len(payload)) + payload)

def send_ack(conn, code=0):
    conn.sendall(bytes([0xA1, 0x00, 0x01, code]))

# ── Command receiver ──────────────────────────────────────────
def cmd_receiver(conn, mode_holder):
    buf = b''
    while True:
        try:
            chunk = conn.recv(64)
            if not chunk: break
            buf += chunk

            while buf:
                tag = buf[0]
                if tag == 0x00 and len(buf) >= 2:
                    mode_holder['mode'] = buf[1]
                    buf = buf[2:]
                elif tag == 0x01 and len(buf) >= 3:
                    handle_button(buf[1], buf[2] == 1)
                    buf = buf[3:]
                elif tag == 0x02 and len(buf) >= 5:
                    lx = struct.unpack('b', bytes([buf[1]]))[0]
                    ly = struct.unpack('b', bytes([buf[2]]))[0]
                    rx = struct.unpack('b', bytes([buf[3]]))[0]
                    ry = struct.unpack('b', bytes([buf[4]]))[0]
                    handle_joystick(lx, ly, rx, ry)
                    buf = buf[5:]
                elif tag == 0x03 and b'\x00' in buf[1:]:
                    end = buf.index(b'\x00', 1)
                    name = buf[1:end].decode(errors='replace')
                    launch_game(name)
                    send_ack(conn)
                    buf = buf[end + 1:]
                elif tag == 0x04 and len(buf) >= 1:
                    # Scan games dynamically across directories
                    refresh_game_list()
                    discovered = list(DYNAMIC_GAMES.keys())
                    running = get_running_windows()
                    
                    # Merge discovered shortcuts and currently running windows, capping at 32 items
                    all_games = list(dict.fromkeys(discovered + running))[:32]
                    send_game_list(conn, all_games)
                    buf = buf[1:]
                elif tag == 0x05 and len(buf) >= 1:
                    release_all()
                    return
                else:
                    break
        except Exception as e:
            print(f"[cmd] {e}")
            break
    release_all()

# ── Frame streamer ────────────────────────────────────────────
def stream_frames(conn, mode_holder, window_title=None):
    frame_ms = 1.0 / TARGET_FPS

    with mss.mss() as sct:
        monitor = sct.monitors[1]

        while True:
            t0 = time.time()

            try:
                region = get_window_region(window_title) if window_title else None
                src    = region if region else monitor

                img = sct.grab(src)
                pil = Image.frombytes('RGB', img.size, img.bgra, 'raw', 'BGRX')
                
                # Extract dimensions before resizing for math mapping
                src_w = src.get("width", monitor["width"])
                src_h = src.get("height", monitor["height"])
                src_left = src.get("left", 0)
                src_top = src.get("top", 0)

                # Downscale the frame to match the ESP32 display
                pil = pil.resize((OUT_W, OUT_H), Image.LANCZOS)

                # MANUALLY DRAW THE MOUSE CURSOR
                try:
                    mx, my = pyautogui.position()
                    # Check if the mouse is currently inside our capture window/screen
                    if src_left <= mx < src_left + src_w and src_top <= my < src_top + src_h:
                        # Translate desktop coordinates to our 320x240 space
                        rel_x = int((mx - src_left) * OUT_W / src_w)
                        rel_y = int((my - src_top) * OUT_H / src_h)
                        
                        # Draw a crisp, distinct red crosshair over the image 
                        # drawing it AFTER resize keeps it perfectly sharp and visible!
                        draw = ImageDraw.Draw(pil)
                        draw.line([(rel_x - 5, rel_y), (rel_x + 5, rel_y)], fill=(255, 0, 0), width=1)
                        draw.line([(rel_x, rel_y - 5), (rel_x, rel_y + 5)], fill=(255, 0, 0), width=1)
                except Exception:
                    pass # Fail silently if mouse coordinates momentarily glitch

                # Save and transmit the JPEG payload
                buf = io.BytesIO()
                pil.save(buf, format='JPEG', quality=JPEG_QUALITY, optimize=False)
                send_frame(conn, buf.getvalue())

            except (BrokenPipeError, ConnectionResetError, OSError):
                print("[stream] ESP32 disconnected")
                break

            elapsed = time.time() - t0
            wait = frame_ms - elapsed
            if wait > 0:
                time.sleep(wait)

# ── Stats ─────────────────────────────────────────────────────
def stats_printer():
    last_f, last_t = 0, time.time()
    while True:
        time.sleep(2)
        now = time.time()
        fps = (stats['frames'] - last_f) / (now - last_t)
        print(f"  {fps:.1f} fps | {stats['bytes']//1024} KB | {stats['cmds']} cmds")
        last_f, last_t = stats['frames'], now

# ── Main ──────────────────────────────────────────────────────
def main():
    threading.Thread(target=broadcast_presence, daemon=True).start()
    threading.Thread(target=stats_printer,      daemon=True).start()
    
    # START THE MOUSE ENGINE: This operates completely independent of network latency!
    threading.Thread(target=mouse_velocity_engine, daemon=True).start()

    srv = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    srv.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    srv.bind((HOST, PORT))
    srv.listen(1)

    import socket as _s
    local_ip = _s.gethostbyname(_s.gethostname())
    print("=" * 50)
    print(f"  PCBridge Server running on IP: {local_ip}")
    print("=" * 50)

    while True:
        try:
            conn, addr = srv.accept()
            conn.setsockopt(socket.IPPROTO_TCP, socket.TCP_NODELAY, 1)
            conn.setsockopt(socket.SOL_SOCKET,  socket.SO_SNDBUF, 128 * 1024)
            print(f"[+] ESP32 connected")

            mode_holder = {'mode': 0, 'game': ''}
            time.sleep(0.1)

            threading.Thread(target=cmd_receiver, args=(conn, mode_holder), daemon=True).start()

            deadline = time.time() + 1.0
            while mode_holder['mode'] == 0 and time.time() < deadline:
                time.sleep(0.05)

            window = mode_holder.get('game') or None
            stream_frames(conn, mode_holder, window_title=window)

            release_all()
            conn.close()
        except KeyboardInterrupt:
            release_all()
            break
        except Exception as e:
            release_all()
            time.sleep(1)
    srv.close()

if __name__ == '__main__':
    main()