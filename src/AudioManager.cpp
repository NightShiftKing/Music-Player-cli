// We define the implementation here — miniaudio is a single-header library.
// This must appear in exactly ONE .cpp file.
#define MINIAUDIO_IMPLEMENTATION
#include "miniaudio.h"

#include "AudioManager.h"
#include <iostream>

AudioManager::AudioManager()
    : engine(nullptr), currentSound(nullptr),
      engineInitialized(false), soundLoaded(false),
      playing(false), volume(64) {}

AudioManager::~AudioManager() {
    cleanup();
}

bool AudioManager::initAudio() {
    engine = new ma_engine();

    ma_result result = ma_engine_init(nullptr, engine);
    if (result != MA_SUCCESS) {
        std::cerr << "Failed to initialize audio engine (error "
                  << result << ")" << std::endl;
        delete engine;
        engine = nullptr;
        return false;
    }

    engineInitialized = true;

    // Set initial volume (0–128 mapped to 0.0–1.0)
    ma_engine_set_volume(engine, static_cast<float>(volume) / 128.0f);

    return true;
}

bool AudioManager::loadAudio(const std::string& filePath) {
    if (!engineInitialized) {
        std::cerr << "Audio engine not initialized." << std::endl;
        return false;
    }

    // Clean up previous sound if loaded
    if (soundLoaded && currentSound != nullptr) {
        ma_sound_uninit(currentSound);
        delete currentSound;
        currentSound = nullptr;
        soundLoaded = false;
        playing = false;
    }

    currentSound = new ma_sound();

    ma_result result = ma_sound_init_from_file(
        engine,
        filePath.c_str(),
        MA_SOUND_FLAG_DECODE,   // Decode upfront for smooth playback
        nullptr,                // No sound group
        nullptr,                // No fence
        currentSound
    );

    if (result != MA_SUCCESS) {
        std::cerr << "Failed to load audio file: " << filePath
                  << " (error " << result << ")" << std::endl;
        delete currentSound;
        currentSound = nullptr;
        return false;
    }

    soundLoaded = true;
    return true;
}

void AudioManager::togglePlayback() {
    if (playing) {
        pause();
    } else {
        play();
    }
}

void AudioManager::play() {
    if (soundLoaded && currentSound != nullptr) {
        ma_sound_start(currentSound);
        playing = true;
    }
}

void AudioManager::pause() {
    if (soundLoaded && currentSound != nullptr) {
        ma_sound_stop(currentSound);
        playing = false;
    }
}

void AudioManager::setVolume(int level) {
    if (level < 0)   level = 0;
    if (level > 128) level = 128;
    volume = level;

    if (engineInitialized && engine != nullptr) {
        ma_engine_set_volume(engine, static_cast<float>(volume) / 128.0f);
    }
}

int AudioManager::getVolume() const {
    return volume;
}

bool AudioManager::getIsPlaying() const {
    // Check if the sound has finished playing naturally
    if (playing && soundLoaded && currentSound != nullptr) {
        if (!ma_sound_is_playing(currentSound)) {
            // Sound finished — cast away const for state update
            const_cast<AudioManager*>(this)->playing = false;
        }
    }
    return playing;
}

void AudioManager::cleanup() {
    if (soundLoaded && currentSound != nullptr) {
        ma_sound_uninit(currentSound);
        delete currentSound;
        currentSound = nullptr;
        soundLoaded = false;
    }

    if (engineInitialized && engine != nullptr) {
        ma_engine_uninit(engine);
        delete engine;
        engine = nullptr;
        engineInitialized = false;
    }

    playing = false;
}
