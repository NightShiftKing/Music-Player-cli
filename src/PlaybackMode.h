// ============================================================
// File: PlaybackMode.h
// Description: Defines the PlaybackMode enum and helper
//              functions for cycling and string conversion.
// ============================================================
#pragma once
#include <string>

enum class PlaybackMode {
    Sequential,
    RepeatAll,
    RepeatOne,
    Shuffle
};

inline PlaybackMode nextPlaybackMode(PlaybackMode mode) {
    switch (mode) {
        case PlaybackMode::Sequential: return PlaybackMode::RepeatAll;
        case PlaybackMode::RepeatAll:  return PlaybackMode::RepeatOne;
        case PlaybackMode::RepeatOne:  return PlaybackMode::Shuffle;
        case PlaybackMode::Shuffle:    return PlaybackMode::Sequential;
    }
    return PlaybackMode::Sequential;
}

inline std::string playbackModeToString(PlaybackMode mode) {
    switch (mode) {
        case PlaybackMode::Sequential: return "➡  Sequential";
        case PlaybackMode::RepeatAll:  return "🔁  Repeat All";
        case PlaybackMode::RepeatOne:  return "🔂  Repeat One";
        case PlaybackMode::Shuffle:    return "🔀  Shuffle";
    }
    return "Unknown";
}
