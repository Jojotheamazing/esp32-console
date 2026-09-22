// MusicTab.h
#pragma once
#include "Scene.h"

class MusicTab : public Scene {
public:
  void onEnter() override;
  void onExit() override;
  void draw() override;
  void onInput(ButtonID btn, InputEvent evt) override;
  void update() override;

private:
  enum class State {
    //OUTPUT_SELECT, //select the output
    FOLDER_LIST, //it will display the folders inside the sd /music
    SONG_LIST, //songs inside a folder
    NOW_PLAYING,  // playing screen maybe will include lyrics
    BLUETOOTH_CONNECT
  };

  State _state = State::FOLDER_LIST;

  //output select removed 
  /*int _selectedOutput = 0;
  int _outputCount = 1;
  static const int OUTPUT_COUNT = 2;
  const char* _outputs[OUTPUT_COUNT] = { "Speakers", "Bluetooth" };*/

  static const int MAX_FOLDERS = 20;
  char _folders[MAX_FOLDERS][64];
  int _folderCount = 0;
  int _selectedFolder = 0;

  static const int MAX_SONGS = 50;
  char _songs[MAX_SONGS][64];
  int _songCount = 0;
  int _selectedSong = 0;

  int _currentAlbum = -1;
  int _currentSong = -1;
  uint32_t currentPos = 0;
  uint32_t songDuration = 0;
  String prevDrawnTime = "";

  bool _isPlaying = false;
  bool _isPaused = false;

  char _currentPath[128];  // "/music/AlbumName/song1.wav"

  void playCurrent();
  void togglePlayback();
  void stopPlayback();
  void drawProgress(uint32_t currentMs, uint32_t totalMs);
  void nextSong();
  void prevSong();

  void drawFolderList();
  void drawSongList();
  void drawNowPlaying();
  void drawBluetoothConnect();
};