// ============================================================
// File: PlayerApp.cpp
// Author: Michael Monreal
// Description: Implements the PlayerApp class. Creates the
//              FTXUI interactive component, composes UI panels
//              using polymorphic UIElement pointers, and handles
//              global keyboard controls for playback and volume.
//              Demonstrates: Polymorphism (UIElement* dispatch).
// ============================================================
#include "PlayerApp.h"
#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>

#include "PlayerApp.h"
#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>
#include <algorithm>
#include <random>

PlayerApp::PlayerApp() 
    : playbackMode(PlaybackMode::Sequential), shuffleIndex(-1) {
    audioManager.initAudio();

    // Seed RNG
    std::random_device rd;
    rng.seed(rd());

    // Create UI panels — stored as UIElement* for polymorphism
    auto nowPlaying    = std::make_unique<NowPlayingPanel>(&playlist, &playbackMode);
    auto playlistPanel = std::make_unique<PlaylistPanel>(&playlist);

    // Keep raw convenience pointers before transferring ownership
    nowPlayingPtr = nowPlaying.get();
    playlistPtr   = playlistPanel.get();

    panels.push_back(std::move(nowPlaying));
    panels.push_back(std::move(playlistPanel));
}

PlayerApp::~PlayerApp() {
    audioManager.cleanup();
}

DoublyLinkedList<SongNode>& PlayerApp::getPlaylist() {
    return playlist;
}

void PlayerApp::cyclePlaybackMode() {
    playbackMode = nextPlaybackMode(playbackMode);
    if (playbackMode == PlaybackMode::Shuffle) {
        buildShuffleOrder();
    }
}

PlaybackMode PlayerApp::getPlaybackMode() const {
    return playbackMode;
}

void PlayerApp::buildShuffleOrder() {
    shuffleOrder.clear();
    int size = playlist.getSize();
    for (int i = 0; i < size; ++i) {
        shuffleOrder.push_back(i);
    }
    std::shuffle(shuffleOrder.begin(), shuffleOrder.end(), rng);
    shuffleIndex = 0;
}

void PlayerApp::advanceTrack() {
    if (playlist.isEmpty()) return;

    switch (playbackMode) {
        case PlaybackMode::Sequential:
            try {
                playlist.traverseForward();
                loadAndPlayCurrent();
            } catch (...) {
                // At the end of sequential, just stop
                audioManager.pause();
                nowPlayingPtr->setPlaying(false);
            }
            break;

        case PlaybackMode::RepeatOne:
            loadAndPlayCurrent();
            break;

        case PlaybackMode::RepeatAll:
            try {
                // If at the last node, wrap around to head
                // DoublyLinkedList::traverseForward() might throw at end or just stay at tail
                // Let's check if we're at tail manually or catch. 
                // Based on implementation, traverseForward doesn't wrap.
                int currentIdx = playlistPtr->getSelectedIndex();
                if (currentIdx == playlist.getSize() - 1) {
                    playlist.resetCurrent();
                } else {
                    playlist.traverseForward();
                }
                loadAndPlayCurrent();
            } catch (...) {
                playlist.resetCurrent();
                loadAndPlayCurrent();
            }
            break;

        case PlaybackMode::Shuffle:
            if (shuffleOrder.empty()) buildShuffleOrder();
            shuffleIndex++;
            if (shuffleIndex >= static_cast<int>(shuffleOrder.size())) {
                buildShuffleOrder();
            }
            
            playlist.resetCurrent();
            for (int i = 0; i < shuffleOrder[shuffleIndex]; ++i) {
                playlist.traverseForward();
            }
            loadAndPlayCurrent();
            break;
    }
}

void PlayerApp::onTrackFinished() {
    if (audioManager.hasFinishedPlaying()) {
        advanceTrack();
    }
}

void PlayerApp::loadAndPlayCurrent() {
    if (!playlist.hasCurrent()) return;
    SongNode& song = playlist.getCurrent();
    if (audioManager.loadAudio(song.getFilePath())) {
        audioManager.play();
        nowPlayingPtr->setPlaying(true);
    }
}

void PlayerApp::run() {
    using namespace ftxui;

    auto screen = ScreenInteractive::Fullscreen();

    // Build the FTXUI component
    auto component = CatchEvent(Renderer([&] {
        // ---- POLLING FOR TRACK END ----
        onTrackFinished();

        // ---- POLYMORPHISM IN ACTION ----
        // Each panel is rendered through the UIElement* interface.
        // The correct render() override is called based on object type.
        std::vector<Element> panelElements;
        for (auto& panel : panels) {
            panelElements.push_back(panel->render());
        }

        // Volume display
        int vol = audioManager.getVolume();
        int volPercent = vol * 100 / 128;
        std::string volStr = "Volume: " + std::to_string(volPercent) + "%";

        auto controlsBox = window(text(" Controls ") | bold,
            vbox({
                text("  " + volStr),
                gauge(static_cast<float>(volPercent) / 100.0f)
                    | color(Color::Green),
                separator(),
                text("  Space: Play/Pause    ↑↓: Navigate List") | dim,
                text("  Enter: Select Song   ←→: Skip Track  ") | dim,
                text("  +/-: Volume          M: Cycle Mode    ") | dim,
                text("  Q: Quit") | dim,
            })
        );

        return vbox({
            text("♪  TUI Music Player  ♪") | bold | center
                | color(Color::Magenta),
            separator(),
            hbox({
                panelElements[0] | flex,  // Now Playing
                separator(),
                panelElements[1] | flex,  // Playlist
            }) | flex,
            controlsBox,
        }) | border;

    }), [&](Event event) {
        // ---- POLYMORPHISM: delegate events to panels ----
        for (auto& panel : panels) {
            if (panel->handleEvent(event)) return true;
        }

        // ---- Global keyboard controls ----

        // Play / Pause
        if (event == Event::Character(' ')) {
            audioManager.togglePlayback();
            nowPlayingPtr->setPlaying(audioManager.getIsPlaying());
            return true;
        }

        // Select song from playlist
        if (event == Event::Return) {
            if (!playlist.isEmpty()) {
                int idx = playlistPtr->getSelectedIndex();
                playlist.resetCurrent();
                for (int i = 0; i < idx; i++) playlist.traverseForward();
                
                // If in shuffle mode, reset shuffle index to this song if it's in the order
                // or just keep it as is. Simplifying: just play.
                loadAndPlayCurrent();
            }
            return true;
        }

        // Cycle Mode
        if (event == Event::Character('m') || event == Event::Character('M')) {
            cyclePlaybackMode();
            return true;
        }

        // Volume up
        if (event == Event::Character('+') || event == Event::Character('=')) {
            audioManager.setVolume(audioManager.getVolume() + 8);
            return true;
        }

        // Volume down
        if (event == Event::Character('-') || event == Event::Character('_')) {
            audioManager.setVolume(audioManager.getVolume() - 8);
            return true;
        }

        // Skip forward
        if (event == Event::ArrowRight) {
            advanceTrack();
            return true;
        }

        // Skip backward
        if (event == Event::ArrowLeft) {
            if (!playlist.isEmpty()) {
                playlist.traverseBackward();
                loadAndPlayCurrent();
            }
            return true;
        }

        // Quit
        if (event == Event::Character('q') || event == Event::Character('Q')) {
            screen.Exit();
            return true;
        }

        return false;
    });

    std::atomic<bool> refresh_ui = true;
    std::thread refresh_thread([&] {
        while (refresh_ui) {
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            screen.PostEvent(Event::Custom);
        }
    });

    screen.Loop(component);
    
    refresh_ui = false;
    refresh_thread.join();
}
