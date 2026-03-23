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

PlayerApp::PlayerApp() {
    audioManager.initAudio();

    // Create UI panels — stored as UIElement* for polymorphism
    auto nowPlaying    = std::make_unique<NowPlayingPanel>(&playlist);
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
                text("  +/-: Volume          Q: Quit          ") | dim,
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
                loadAndPlayCurrent();
            }
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
            if (!playlist.isEmpty()) {
                playlist.traverseForward();
                loadAndPlayCurrent();
            }
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

    screen.Loop(component);
}
