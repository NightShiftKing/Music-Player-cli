// ============================================================
// File: NowPlayingPanel.h
// Author: Michael Monreal
// Description: Concrete UI panel that displays the currently
//              playing song's metadata and playback state.
//              Inherits from UIElement and overrides render(),
//              handleEvent(), and getName().
//              Demonstrates: Inheritance, Polymorphism.
// ============================================================
#pragma once
#include "UIElement.h"
#include "DoublyLinkedList.h"
#include "SongNode.h"
#include "PlaybackMode.h"
#include <ftxui/dom/elements.hpp>

class NowPlayingPanel : public UIElement {
private:
    DoublyLinkedList<SongNode>* playlist;  // Non-owning pointer
    PlaybackMode* currentMode;             // Non-owning pointer
    bool isPlaying;

public:
    NowPlayingPanel(DoublyLinkedList<SongNode>* pl, PlaybackMode* mode)
        : playlist(pl), currentMode(mode), isPlaying(false) {}

    void setPlaying(bool playing) { isPlaying = playing; }

    // ---- Overridden pure virtual methods ----

    ftxui::Element render() override {
        using namespace ftxui;

        if (playlist->isEmpty()) {
            return window(text(" Now Playing ") | bold,
                text("  No songs loaded  ") | center | dim
            );
        }

        SongNode& song = playlist->getCurrent();
        std::string status = isPlaying ? "▶  Playing" : "⏸  Paused";
        std::string modeStr = currentMode ? playbackModeToString(*currentMode) : "";

        return window(text(" Now Playing ") | bold,
            vbox({
                text("  " + song.getTitle()) | bold,
                text("  " + song.getArtist()) | dim,
                text("  " + song.getAlbum()) | dim,
                separator(),
                hbox({
                    text("  " + status)
                        | (isPlaying ? color(Color::Green) : color(Color::Yellow)),
                    filler(),
                    text(modeStr + "  ") | dim,
                }),
            })
        );
    }

    bool handleEvent(ftxui::Event event) override {
        // NowPlayingPanel does not handle events directly
        return false;
    }

    std::string getName() const override {
        return "Now Playing";
    }
};
