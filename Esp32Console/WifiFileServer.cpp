#include "WiFiFileServer.h"
#include "sdCard.h"
#include <WiFi.h>
#include <WebServer.h>
#include <ArduinoJson.h>
#include <SD.h>

static WebServer _server(80);
static bool _running = false;
static WfsMode _mode = WfsMode::AP;


static const char UI_HTML[] PROGMEM = R"rawhtml(
<!DOCTYPE html>
<html lang="en">
<head>
<meta charset="UTF-8">
<meta name="viewport" content="width=device-width, initial-scale=1">
<title>SD File Manager</title>
<style>
  * { box-sizing: border-box; margin: 0; padding: 0; }
  body { font-family: monospace; background: #1a1a1a; color: #e0e0e0; padding: 16px; }
  h1 { color: #f0c040; margin-bottom: 12px; font-size: 1.2rem; }
  #path-bar { background: #2a2a2a; padding: 8px 12px; border-radius: 4px;
              margin-bottom: 10px; font-size: 0.9rem; color: #aaa; word-break: break-all; }
  #toolbar { display: flex; gap: 8px; flex-wrap: wrap; margin-bottom: 12px; }
  button { background: #333; color: #e0e0e0; border: 1px solid #555;
           padding: 6px 12px; border-radius: 4px; cursor: pointer; font-family: monospace; }
  button:hover { background: #444; }
  button.danger { color: #f06060; border-color: #f06060; }
  #drop-zone { border: 2px dashed #555; border-radius: 6px; padding: 16px;
               text-align: center; color: #666; margin-bottom: 12px;
               transition: border-color 0.2s, color 0.2s; }
  #drop-zone.over { border-color: #f0c040; color: #f0c040; }
  #file-list { border: 1px solid #333; border-radius: 4px; }
  .entry { display: flex; align-items: center; padding: 8px 10px;
           border-bottom: 1px solid #2a2a2a; gap: 8px; }
  .entry:last-child { border-bottom: none; }
  .entry:hover { background: #242424; }
  .icon { width: 18px; text-align: center; flex-shrink: 0; }
  .name { flex: 1; cursor: pointer; word-break: break-all; }
  .name:hover { color: #f0c040; }
  .size { color: #666; font-size: 0.8rem; flex-shrink: 0; }
  .entry-btns { display: flex; gap: 4px; flex-shrink: 0; }
  .entry-btns button { padding: 2px 7px; font-size: 0.75rem; }
  #status { margin-top: 10px; color: #f0c040; font-size: 0.85rem; min-height: 1.2em; }
  #editor-modal { display: none; position: fixed; inset: 0; background: rgba(0,0,0,0.8);
                  align-items: center; justify-content: center; }
  #editor-modal.open { display: flex; }
  #editor-box { background: #1e1e1e; border: 1px solid #555; border-radius: 6px;
                padding: 16px; width: 92vw; max-width: 820px; display: flex;
                flex-direction: column; gap: 10px; max-height: 90vh; }
  #editor-box h2 { color: #f0c040; font-size: 1rem; word-break: break-all; }
  #editor-ta { flex: 1; background: #111; color: #e0e0e0; border: 1px solid #444;
               border-radius: 4px; padding: 10px; font-family: monospace;
               font-size: 0.85rem; resize: none; min-height: 50vh; white-space: pre; }
  #editor-footer { display: flex; gap: 8px; justify-content: flex-end; }
  #upload-progress { display: none; margin-top: 6px; height: 6px;
                     background: #333; border-radius: 3px; overflow: hidden; }
  #upload-bar { height: 100%; width: 0; background: #f0c040;
                transition: width 0.1s; }
</style>
</head>
<body>
<h1>📁 SD File Manager</h1>
<div id="path-bar">/</div>

<div id="toolbar">
  <button onclick="goUp()">⬆ Up</button>
  <button onclick="mkdirPrompt()">📂 New Folder</button>
  <button onclick="document.getElementById('file-input').click()">⬆ Upload</button>
  <input id="file-input" type="file" multiple style="display:none"
         onchange="uploadFiles(this.files)">
</div>

<div id="drop-zone">Drop files here to upload to current folder</div>
<div id="upload-progress"><div id="upload-bar"></div></div>

<div id="file-list"></div>
<div id="status"></div>

<!-- Editor modal -->
<div id="editor-modal">
  <div id="editor-box">
    <h2 id="editor-title">Editing: </h2>
    <textarea id="editor-ta" spellcheck="false"></textarea>
    <div id="editor-footer">
      <button onclick="closeEditor()">Cancel</button>
      <button onclick="saveEditor()" style="color:#f0c040;border-color:#f0c040">💾 Save</button>
    </div>
  </div>
</div>

<script>
let currentPath = '/';
let editingPath = '';

function setStatus(msg) { document.getElementById('status').textContent = msg; }

function joinPath(base, name) {
  if (base === '/') return '/' + name;
  return base.replace(/\/+$/, '') + '/' + name;
}

function fmtSize(bytes) {
  if (bytes < 1024) return bytes + ' B';
  if (bytes < 1048576) return (bytes/1024).toFixed(1) + ' KB';
  return (bytes/1048576).toFixed(1) + ' MB';
}

async function listDir(path) {
  currentPath = path;
  document.getElementById('path-bar').textContent = path;
  setStatus('Loading…');
  try {
    const r = await fetch('/list?path=' + encodeURIComponent(path));
    const entries = await r.json();
    renderList(entries);
    setStatus('');
  } catch(e) { setStatus('Error loading directory'); }
}

function renderList(entries) {
  const el = document.getElementById('file-list');
  if (!entries.length) { el.innerHTML = '<div class="entry" style="color:#555">Empty folder</div>'; return; }
  entries.sort((a,b) => {
    if (a.isDir !== b.isDir) return a.isDir ? -1 : 1;
    return a.name.localeCompare(b.name);
  });
  el.innerHTML = entries.map(e => `
    <div class="entry">
      <span class="icon">${e.isDir ? '📁' : '📄'}</span>
      <span class="name" onclick="${e.isDir ? `listDir('${joinPath(currentPath,e.name)}')` : `openFile('${joinPath(currentPath,e.name)}')`}">${e.name}</span>
      ${!e.isDir ? `<span class="size">${fmtSize(e.size)}</span>` : ''}
      <div class="entry-btns">
        <button onclick="downloadFile('${joinPath(currentPath,e.name)}')">⬇</button>
        <button onclick="renamePrompt('${joinPath(currentPath,e.name)}','${e.name}')">✏</button>
        <button class="danger" onclick="deleteEntry('${joinPath(currentPath,e.name)}','${e.isDir}')">🗑</button>
      </div>
    </div>`).join('');
}

function goUp() {
  if (currentPath === '/') return;
  const parts = currentPath.replace(/\/+$/,'').split('/');
  parts.pop();
  listDir(parts.join('/') || '/');
}

async function openFile(path) {
  const ext = path.split('.').pop().toLowerCase();
  const textTypes = ['lua','txt','json','cfg','ini','md','h','cpp','py','js','html','css'];
  if (textTypes.includes(ext)) {
    setStatus('Opening…');
    const r = await fetch('/file?path=' + encodeURIComponent(path));
    const text = await r.text();
    editingPath = path;
    document.getElementById('editor-title').textContent = 'Editing: ' + path;
    document.getElementById('editor-ta').value = text;
    document.getElementById('editor-modal').classList.add('open');
    setStatus('');
  } else {
    window.location = '/file?path=' + encodeURIComponent(path);
  }
}


async function saveEditor() {
  const content = document.getElementById('editor-ta').value;
  const blob = new Blob([content], {type:'text/plain'});
  const fname = editingPath.split('/').pop();
  const folder = editingPath.substring(0, editingPath.lastIndexOf('/')) || '/';
  const fd = new FormData();
  fd.append('file', blob, fname);
  setStatus('Saving…');
  const r = await fetch('/upload?path=' + encodeURIComponent(folder), {method:'POST', body:fd});
  if (r.ok) { setStatus('Saved ✓'); closeEditor(); listDir(currentPath); }
  else setStatus('Save failed');
}

function closeEditor() {
  document.getElementById('editor-modal').classList.remove('open');
  editingPath = '';
}

async function uploadFiles(files) {
  for (const file of files) {
    await uploadOne(file);
  }
  listDir(currentPath);
}

function uploadOne(file) {
  return new Promise(resolve => {
    const fd = new FormData();
    fd.append('file', file, file.name);
    const xhr = new XMLHttpRequest();
    const bar = document.getElementById('upload-bar');
    const prog = document.getElementById('upload-progress');
    prog.style.display = 'block';
    bar.style.width = '0';
    setStatus('Uploading ' + file.name + '…');
    xhr.upload.onprogress = e => {
      if (e.lengthComputable) bar.style.width = (e.loaded/e.total*100) + '%';
    };
    xhr.onload = () => {
      prog.style.display = 'none';
      setStatus(xhr.status === 200 ? 'Uploaded ' + file.name + ' ✓' : 'Upload failed');
      resolve();
    };
    xhr.onerror = () => { setStatus('Upload error'); resolve(); };
    xhr.open('POST', '/upload?path=' + encodeURIComponent(currentPath));
    xhr.send(fd);
  });
}
function downloadFile(path) {
  window.location = '/file?path=' + encodeURIComponent(path) + '&download=1';
}

const dz = document.getElementById('drop-zone');
dz.addEventListener('dragover', e => { e.preventDefault(); dz.classList.add('over'); });
dz.addEventListener('dragleave', () => dz.classList.remove('over'));
dz.addEventListener('drop', e => {
  e.preventDefault(); dz.classList.remove('over');
  uploadFiles(e.dataTransfer.files);
});

async function deleteEntry(path, isDir) {
  if (!confirm('Delete ' + path + '?')) return;
  setStatus('Deleting…');
  const r = await fetch('/delete', {
    method:'POST',
    headers:{'Content-Type':'application/json'},
    body: JSON.stringify({path})
  });
  setStatus(r.ok ? 'Deleted ✓' : 'Delete failed');
  listDir(currentPath);
}

async function renamePrompt(path, oldName) {
  const newName = prompt('Rename to:', oldName);
  if (!newName || newName === oldName) return;
  const folder = path.substring(0, path.lastIndexOf('/')) || '/';
  const newPath = joinPath(folder, newName);
  setStatus('Renaming…');
  const r = await fetch('/rename', {
    method:'POST',
    headers:{'Content-Type':'application/json'},
    body: JSON.stringify({from: path, to: newPath})
  });
  setStatus(r.ok ? 'Renamed ✓' : 'Rename failed');
  listDir(currentPath);
}

async function mkdirPrompt() {
  const name = prompt('Folder name:');
  if (!name) return;
  const path = joinPath(currentPath, name);
  setStatus('Creating…');
  const r = await fetch('/mkdir', {
    method:'POST',
    headers:{'Content-Type':'application/json'},
    body: JSON.stringify({path})
  });
  setStatus(r.ok ? 'Created ✓' : 'Create failed');
  listDir(currentPath);
}

listDir('/');
</script>
</body>
</html>
)rawhtml";


static void handleRoot() {
  _server.send_P(200, "text/html", UI_HTML);
}


static void handleList() {
  String path = _server.arg("path");
  if (path.isEmpty()) path = "/";

  File dir = SD.open(path.c_str());
  if (!dir || !dir.isDirectory()) {
    _server.send(404, "application/json", "[]");
    return;
  }

  String json = "[";
  bool first = true;
  File f = dir.openNextFile();
  while (f) {
    if (!first) json += ",";
    first = false;
    json += "{\"name\":\"";
    json += f.name();
    json += "\",\"isDir\":";
    json += f.isDirectory() ? "true" : "false";
    if (!f.isDirectory()) {
      json += ",\"size\":";
      json += f.size();
    }
    json += "}";
    f.close();
    f = dir.openNextFile();
  }
  json += "]";
  dir.close();
  _server.send(200, "application/json", json);
}


static void handleFileGet() {
  String path = _server.arg("path");
  bool download = _server.hasArg("download");

  if (path.isEmpty() || !SD.exists(path.c_str())) {
    _server.send(404, "text/plain", "Not found");
    return;
  }

  File f = SD.open(path.c_str());
  if (!f) {
    _server.send(500, "text/plain", "Open failed");
    return;
  }

  if (download) {
    String filename = path.substring(path.lastIndexOf('/') + 1);
    _server.sendHeader("Content-Disposition", "attachment; filename=" + filename);
  }

  String mime = "application/octet-stream";
  String lp = path;
  lp.toLowerCase();
  if (lp.endsWith(".txt") || lp.endsWith(".lua") || lp.endsWith(".md"))
    mime = "text/plain";
  else if (lp.endsWith(".json")) mime = "application/json";
  else if (lp.endsWith(".jpg") || lp.endsWith(".jpeg")) mime = "image/jpeg";
  else if (lp.endsWith(".bmp")) mime = "image/bmp";
  else if (lp.endsWith(".html")) mime = "text/html";

  _server.streamFile(f, mime);
  f.close();
}


static void handleUpload() {
  HTTPUpload& upload = _server.upload();

  static File uploadFile;

  if (upload.status == UPLOAD_FILE_START) {
    String folder = _server.arg("path");
    if (folder.isEmpty()) folder = "/";

    String dest = folder;
    if (!dest.endsWith("/")) dest += "/";
    dest += upload.filename;

    if (SD.exists(dest.c_str())) SD.remove(dest.c_str());
    uploadFile = SD.open(dest.c_str(), FILE_WRITE);
    Serial.printf("[WFS] Upload start: %s\n", dest.c_str());
  } else if (upload.status == UPLOAD_FILE_WRITE) {
    if (uploadFile) uploadFile.write(upload.buf, upload.currentSize);
  } else if (upload.status == UPLOAD_FILE_END) {
    if (uploadFile) { uploadFile.close(); }
    Serial.printf("[WFS] Upload done: %u bytes\n", upload.totalSize);
    _server.send(200, "text/plain", "OK");
  }
}

static void handleDelete() {
  StaticJsonDocument<256> doc;
  if (deserializeJson(doc, _server.arg("plain"))) {
    _server.send(400, "text/plain", "Bad JSON");
    return;
  }
  const char* path = doc["path"];
  if (!path) {
    _server.send(400, "text/plain", "No path");
    return;
  }

  bool ok = false;
  if (SD.exists(path)) {
    File f = SD.open(path);
    bool isDir = f.isDirectory();
    f.close();
    ok = isDir ? SD.rmdir(path) : SD.remove(path);
  }
  _server.send(ok ? 200 : 500, "text/plain", ok ? "OK" : "Failed");
  Serial.printf("[WFS] Delete %s: %s\n", path, ok ? "ok" : "fail");
}

static void handleRename() {
  StaticJsonDocument<512> doc;
  if (deserializeJson(doc, _server.arg("plain"))) {
    _server.send(400, "text/plain", "Bad JSON");
    return;
  }

  String from = doc["from"].as<String>();
  String to = doc["to"].as<String>();

  if (from.length() == 0 || to.length() == 0) {
    _server.send(400, "text/plain", "Missing fields");
    return;
  }

  if (SD.exists(to.c_str())) {
    File f = SD.open(from.c_str());
    bool isDir = f.isDirectory();
    f.close();

    if (isDir) SD.rmdir(to.c_str());
    else SD.remove(to.c_str());
  }

  bool ok = SD.rename(from.c_str(), to.c_str());

  Serial.printf("[WFS] Rename %s -> %s: %s\n",
                from.c_str(), to.c_str(), ok ? "ok" : "fail");

  _server.send(ok ? 200 : 500, "text/plain", ok ? "OK" : "Failed");
}

static void handleMkdir() {
  StaticJsonDocument<256> doc;
  if (deserializeJson(doc, _server.arg("plain"))) {
    _server.send(400, "text/plain", "Bad JSON");
    return;
  }
  const char* path = doc["path"];
  if (!path) {
    _server.send(400, "text/plain", "No path");
    return;
  }

  bool ok = SD.mkdir(path);
  _server.send(ok ? 200 : 500, "text/plain", ok ? "OK" : "Failed");
  Serial.printf("[WFS] Mkdir %s: %s\n", path, ok ? "ok" : "fail");
}


bool wfsStart(WfsMode mode, const char* ssid, const char* password, uint32_t timeoutMs) {
  if (_running) return true;
  if (!sdReady) {
    Serial.println("[WFS] SD not ready");
    return false;
  }
  _mode = mode;

  if (mode == WfsMode::STA) {
    Serial.printf("[WFS] Connecting to %s …\n", ssid);
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    uint32_t start = millis();
    while (WiFi.status() != WL_CONNECTED) {
      if (millis() - start > timeoutMs) {
        Serial.println("[WFS] Wi-Fi timeout");
        WiFi.disconnect(true);
        return false;
      }
      delay(200);
    }
    Serial.printf("[WFS] Connected — IP: %s\n", WiFi.localIP().toString().c_str());
  } else {
    WiFi.mode(WIFI_AP);
    WiFi.softAP(ssid, strlen(password) ? password : nullptr);
    delay(100);
    Serial.printf("[WFS] AP '%s' started — open http://%s\n",
                  ssid, WiFi.softAPIP().toString().c_str());
  }

  _server.on("/", HTTP_GET, handleRoot);
  _server.on("/list", HTTP_GET, handleList);
  _server.on("/file", HTTP_GET, handleFileGet);
  _server.on("/delete", HTTP_POST, handleDelete);
  _server.on("/rename", HTTP_POST, handleRename);
  _server.on("/mkdir", HTTP_POST, handleMkdir);
  _server.on(
    "/upload", HTTP_POST,
    []() {},
    handleUpload);
  _server.begin();
  _running = true;
  Serial.println("[WFS] Server started");
  return true;
}

void wfsLoop() {
  if (_running) _server.handleClient();
}

void wfsStop() {
  if (!_running) return;
  _server.close();
  WiFi.disconnect(true);
  WiFi.mode(WIFI_OFF);
  _running = false;
  Serial.println("[WFS] Stopped, Wi-Fi off");
}

bool wfsRunning() {
  return _running;
}
String wfsIP() {
  if (!_running) return "";
  return (_mode == WfsMode::STA)
           ? WiFi.localIP().toString()
           : WiFi.softAPIP().toString();
}