#pragma once
#include "UIElement.h"
#include "DoublyLinkedList.h"
#include "SongNode.h"
#include <ftxui/dom/elements.hpp>

// ============================================================
// NowPlayingPanel — Displays the currently playing song.
// Demonstrates: Inheritance (from UIElement),
//               Polymorphism (overrides render, handleEvent, getName)
// ============================================================
class NowPlayingPanel : public UIElement {
private:
    DoublyLinkedList<SongNode>* playlist;  // Non-owning pointer
    bool isPlaying;

public:
    NowPlayingPanel(DoublyLinkedList<SongNode>* pl)
        : playlist(pl), isPlaying(false) {}

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

        return window(text(" Now Playing ") | bold,
            vbox({
                text("  " + song.title) | bold,
                text("  " + song.artist) | dim,
                text("  " + song.album) | dim,
                separator(),
                text("  " + status)
                    | (isPlaying ? color(Color::Green) : color(Color::Yellow)),
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
