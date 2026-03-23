#pragma once
#include <string>

// ============================================================
// AudioManager — Cross-platform audio playback via miniaudio.
// Supports: WAV, MP3, FLAC, Vorbis on Windows, macOS, Linux.
// Demonstrates: Encapsulation, Resource Management,
//               Concurrency (audio decoding/streaming on its own thread)
// ============================================================

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
