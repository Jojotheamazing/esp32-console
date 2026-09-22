#include <Arduino.h>
#include <ArduinoJson.h>
#include "MusicTab.h"
#include <Arduino.h>
#include "ButtonManager.h"
#include "sdCard.h"
#include "display.h"
#include "MyFonts.h"
#include "SettingsManager.h"
#include "I2SAudio.h"
//#include "BTAudio.h"
#include "AudioHandler.h"
#include "Preferences.h"

String stripExtension(const char* filename) {
  String s = String(filename);
  int dot = s.lastIndexOf('.');
  return dot >= 0 ? s.substring(0, dot) : s;
}

void MusicTab::playCurrent() {
  snprintf(_currentPath, sizeof(_currentPath), "/music/%s/%s",
           _folders[_currentAlbum], _songs[_currentSong]);

  playSound(_currentPath);

  _isPlaying = true;
  _isPaused = false;
  currentPos = 0;
  songDuration = getAudioDurationI2S();
  //songDuration = getWavDurationMs(_currentPath);
  draw();
}

void MusicTab::togglePlayback() {
  if (_currentSong == -1) return;
  pauseSound();
  if (_isPlaying && !_isPaused) {
    _isPaused = true;
    drawNowPlaying();
  } else if (_isPaused) {
    _isPaused = false;
    drawNowPlaying();
  } else {
    playCurrent();
  }
}

void MusicTab::stopPlayback() {
  stopSound();
  _isPlaying = false;
  _isPaused = false;
}

void MusicTab::nextSong() {
  _currentSong++;
  if (_currentSong >= _songCount) {
    _currentSong = 0;
    _currentAlbum = (_currentAlbum + 1) % _folderCount;
    char path[80];
    snprintf(path, sizeof(path), "/music/%s", _folders[_currentAlbum]);
    _songCount = loadFileNames(path, _songs, MAX_SONGS);
  }
  playCurrent();
}

void MusicTab::prevSong() {
  _currentSong--;
  if (_currentSong < 0) {
    //go to previous album
    _currentAlbum = (_currentAlbum - 1 + _folderCount) % _folderCount;
    char path[80];
    snprintf(path, sizeof(path), "/music/%s", _folders[_currentAlbum]);
    _songCount = loadFileNames(path, _songs, MAX_SONGS);
    _currentSong = _songCount - 1;  //last song of previous album
  }
  playCurrent();
}

void MusicTab::onEnter() {
  _state = State::FOLDER_LIST;
  _folderCount = loadFileNames("/music", _folders, MAX_FOLDERS, true);
  _selectedFolder = 0;
  Serial.println("[Music] entered");
  draw();
}

void MusicTab::onExit() {
  stopPlayback();

  Serial.println("[Music] exited");
}


void MusicTab::draw() {
  switch (_state) {
    //case State::OUTPUT_SELECT: drawOutputSelect(); break;
    case State::FOLDER_LIST: drawFolderList(); break;
    case State::SONG_LIST: drawSongList(); break;
    case State::NOW_PLAYING: drawNowPlaying(); break;
  }
}

void MusicTab::drawFolderList() {
  tft.fillScreen(COLOR_BG);
  const int maxVisible = 5;

  const int listYOffset = 70;
  const int itemHeight = (tft.height() - 60) / maxVisible;

  int scrollOffset = 0;
  if (_selectedFolder >= maxVisible) scrollOffset = _selectedFolder - maxVisible + 1;
  int displayStart = scrollOffset;
  int displayEnd = min(scrollOffset + maxVisible, _folderCount);

  tft.setFreeFont(&FONT_TITLE);
  tft.setTextDatum(TC_DATUM);
  tft.setTextColor(COLOR_TEXT);
  tft.drawString("Albums/Playlists", tft.width() / 2, 10);

  for (int i = displayStart; i < displayEnd; i++) {
    int screenIndex = i - scrollOffset;
    int yPos = listYOffset + itemHeight * screenIndex;
    bool isSelected = (i == _selectedFolder);
    tft.setCursor(10, yPos);
    tft.setFreeFont(&FONT_BODY);
    tft.setTextColor(isSelected ? COLOR_SELECTED : COLOR_TEXT);
    tft.print(String(i + 1) + "." + String(_folders[i]));
  }

  if (scrollOffset > 0) {
    tft.fillTriangle(
      tft.width() - 20, 15,
      tft.width() - 10, 15,
      tft.width() - 15, 5,
      COLOR_HINT);
  }
  if (displayEnd < _folderCount) {
    int downY = listYOffset + maxVisible * itemHeight;
    tft.fillTriangle(
      tft.width() - 20, tft.height() - 15,
      tft.width() - 10, tft.height() - 15,
      tft.width() - 15, tft.height() - 5,
      COLOR_HINT);
  }
}

void MusicTab::drawSongList() {
  tft.fillScreen(COLOR_BG);
  const int maxVisible = 5;

  const int listYOffset = 70;
  const int itemHeight = (tft.height() - 60) / maxVisible;

  int scrollOffset = 0;
  if (_selectedSong >= maxVisible) scrollOffset = _selectedSong - maxVisible + 1;
  int displayStart = scrollOffset;
  int displayEnd = min(scrollOffset + maxVisible, _songCount);

  tft.setFreeFont(&FONT_TITLE);
  tft.setTextDatum(TC_DATUM);
  tft.setTextColor(COLOR_TEXT);
  tft.drawString(String(_folders[_selectedFolder]), tft.width() / 2, 10);

  for (int i = displayStart; i < displayEnd; i++) {
    int screenIndex = i - scrollOffset;
    int yPos = listYOffset + itemHeight * screenIndex;
    bool isSelected = (i == _selectedSong);
    tft.setCursor(10, yPos);
    tft.setFreeFont(&FONT_BODY);
    tft.setTextColor(isSelected ? COLOR_SELECTED : COLOR_TEXT);
    tft.print(String(i + 1) + "." + String(stripExtension(_songs[i])));
  }

  if (scrollOffset > 0) {
    tft.fillTriangle(
      tft.width() - 20, 15,
      tft.width() - 10, 15,
      tft.width() - 15, 5,
      COLOR_HINT);
  }
  if (displayEnd < _songCount) {
    int downY = listYOffset + maxVisible * itemHeight;
    tft.fillTriangle(
      tft.width() - 20, tft.height() - 15,
      tft.width() - 10, tft.height() - 15,
      tft.width() - 15, tft.height() - 5,
      COLOR_HINT);
  }
}

void MusicTab::drawNowPlaying() {
  tft.fillScreen(COLOR_BG);
  drawProgress(getAudioPos(), songDuration);
  const int iconPanelW = 60;
  const int contentW = tft.width() - iconPanelW;

  tft.setFreeFont(&FF23);
  tft.setTextDatum(ML_DATUM);
  tft.setTextColor(COLOR_TEXT);
  tft.drawString(stripExtension(_songs[_currentSong]),15 , 172);

  char coverPath[128];
  snprintf(coverPath, sizeof(coverPath), "/music/%s/cover.jpg", _folders[_currentAlbum]);

  const int coverSize = 128;

  if (SD.exists(coverPath)) {
    drawJpg(coverPath,40,20 );
  } else {
    tft.fillRect((contentW - coverSize) / 2, (tft.height() - coverSize) / 2 - 13,
                 coverSize, coverSize, COLOR_HINT);
  }

  char infoPath[128];
  snprintf(infoPath, sizeof(infoPath), "/music/%s/info.json", _folders[_currentAlbum]);

  tft.setFreeFont(&FF17);
  tft.setTextDatum(ML_DATUM);
  tft.setTextColor(COLOR_HINT);

  //tft.drawString(String(_folders[_currentAlbum]), 148, 86);

  if (SD.exists(infoPath)) {
    File f = SD.open(infoPath);
    StaticJsonDocument<256> doc;
    if (!deserializeJson(doc, f)) {
      tft.setTextColor(COLOR_HINT);
      tft.drawString(doc["artist"] | "Unknown", 15, 197);
    }
    f.close();
  }

  drawJpg(_isPaused ? "/Assets/UIImages/MusicTab/resume.jpg" :"/Assets/UIImages/MusicTab/pause.jpg",273,68);
  drawJpg("/Assets/UIImages/MusicTab/fast-forward.jpg",273,116);
  drawJpg("/Assets/UIImages/MusicTab/fast-backward.jpg",273,20);

}

String formatTime(uint32_t ms) {
  uint32_t totalSeconds = ms / 1000;
  uint32_t minutes = totalSeconds / 60;
  uint32_t seconds = totalSeconds % 60;

  char buf[10];
  snprintf(buf, sizeof(buf), "%02lu:%02lu", minutes, seconds);

  return String(buf);
}

void MusicTab::drawProgress(uint32_t currentMs, uint32_t totalMs) {
  const int iconPanelW = 60;

  int barY = 216;
  int barH = 9;

  int screenW = tft.width() - iconPanelW;

  int barX = 50;
  int barW = 220;

  tft.fillRect(0, 212, 320, 17, COLOR_BG);

  tft.setFreeFont(&FONT_SMALL);
  tft.setTextColor(COLOR_TEXT);
  tft.setTextDatum(ML_DATUM);
  tft.drawString(formatTime(currentMs), 0, 220);

  tft.setTextDatum(MR_DATUM);
  tft.drawString(formatTime(totalMs), 320, 220);

  tft.fillRoundRect(barX, barY, barW, barH, 3, COLOR_HINT);

  if (totalMs == 0) return;

  float progress = (float)currentMs / totalMs;
  progress = constrain(progress, 0.0f, 1.0f);

  int filledW = progress * barW;

  tft.fillRoundRect(barX, barY, filledW, barH, 3, COLOR_SELECTED);

  tft.fillCircle(barX + filledW, 220, 8.5, COLOR_TEXT);
  prevDrawnTime = formatTime(currentMs);
}


void MusicTab::onInput(ButtonID btn, InputEvent evt) {
  if (evt != EVT_PRESSED && evt != EVT_REPEAT) return;

  switch (_state) {
    /*case State::OUTPUT_SELECT:
      if (btn == BTN_B && evt == EVT_PRESSED) {
        exit();
        onExit();
        return;
      }
      if (btn == BTN_DOWN) {
        _selectedOutput = (_selectedOutput + 1) % _outputCount;
        draw();
      }
      if (btn == BTN_UP) {
        _selectedOutput = (_selectedOutput - 1 + _outputCount) % _outputCount;

        draw();
      }
      if (btn == BTN_A && evt == EVT_PRESSED) {
        _folderCount = loadFileNames("/music", _folders, MAX_FOLDERS, true);
        _selectedFolder = 0;
        //_selectedOutput = 0;
        _state = State::FOLDER_LIST;
        draw();
      }
      break;
    */
    case State::FOLDER_LIST:
      if (btn == BTN_B && evt == EVT_PRESSED) {
        exit();
        onExit();
        return;
      }
      if (btn == BTN_DOWN) {
        _selectedFolder = (_selectedFolder + 1) % _folderCount;
        draw();
      }
      if (btn == BTN_UP) {
        _selectedFolder = (_selectedFolder - 1 + _folderCount) % _folderCount;
        draw();
      }
      if (btn == BTN_A && evt == EVT_PRESSED) {
        char path[80];
        snprintf(path, sizeof(path), "/music/%s", _folders[_selectedFolder]);
        _songCount = loadFileNames(path, _songs, MAX_SONGS);
        _selectedSong = 0;
        _state = State::SONG_LIST;
        draw();
      }
      break;

    case State::SONG_LIST:
      if (btn == BTN_B && evt == EVT_PRESSED) {
        _state = State::FOLDER_LIST;
        draw();
        return;
      }
      if (btn == BTN_DOWN) {
        _selectedSong = (_selectedSong + 1) % _songCount;
        draw();
      }
      if (btn == BTN_UP) {
        _selectedSong = (_selectedSong - 1 + _songCount) % _songCount;
        draw();
      }
      if (btn == BTN_A && evt == EVT_PRESSED) {
        _currentAlbum = _selectedFolder;
        _currentSong = _selectedSong;

        _state = State::NOW_PLAYING;
        playCurrent();
      }
      break;

    case State::NOW_PLAYING:
      if (btn == BTN_A && evt == EVT_PRESSED) togglePlayback();
      if (btn == BTN_RIGHT && evt == EVT_PRESSED) nextSong();
      if (btn == BTN_LEFT && evt == EVT_PRESSED) prevSong();
      if (btn == BTN_B && evt == EVT_PRESSED) {
        _state = State::SONG_LIST;
        draw();
        return;
      }
      break;
  }
}

void MusicTab::update() {


  /*if (_state != State::NOW_PLAYING) return;
  if (!_isPlaying || _isPaused) return;

  if (millis() - lastUpdate > 200) {
    lastUpdate = millis();

    currentPos += 200;

    if (currentPos > songDuration) {
      currentPos = songDuration;

      // optional auto-next
      nextSong();
    }

    drawProgress(currentPos, songDuration);
  }*/

  static uint32_t lastUpdate = 0;
  if (_state != State::NOW_PLAYING || isPlayingI2S() == false) return;
  if (songDuration == 0) {
    songDuration = getAudioDurationI2S();
    return;
  }
  /*if (settings.audioOutput == 1) {
    if (millis() - lastUpdate > 1000) {
      lastUpdate = millis();
      if (getAudioPos() > songDuration) {
        nextSong();
      }

      drawProgress(getAudioPos() * 1000, songDuration * 1000);
    }
  }*/
}