// ============================================================
// File: AudioManager.h
// Author: Michael Monreal
// Description: Declares the AudioManager class which handles
//              cross-platform audio playback using miniaudio.
//              Supports WAV, MP3, FLAC, and Vorbis formats.
//              Demonstrates: Encapsulation, Resource Management,
//              Concurrency (audio streaming on a background thread).
// ============================================================
#pragma once
#include <string>

// Forward declarations (avoids exposing miniaudio.h in the header)
struct ma_engine;
struct ma_sound;

class AudioManager {
private:
    ma_engine* engine;
    ma_sound*  currentSound;
    bool engineInitialized;
    bool soundLoaded;
    bool playing;
    int  volume;  // 0–128

public:
    AudioManager();
    ~AudioManager();

    bool initAudio();
    bool loadAudio(const std::string& filePath);
    void togglePlayback();
    void play();
    void pause();
    void setVolume(int level);
    int  getVolume() const;
    bool getIsPlaying() const;
    void cleanup();
};
