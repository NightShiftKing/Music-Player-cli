// ============================================================
// File: PlaylistPanel.h
// Author: Michael Monreal
// Description: Concrete UI panel that displays the song list
//              with arrow-key navigation and selection.
//              Inherits from UIElement and overrides render(),
//              handleEvent(), and getName().
//              Demonstrates: Inheritance, Polymorphism.
// ============================================================
#pragma once
#include "UIElement.h"
#include "DoublyLinkedList.h"
#include "SongNode.h"
#include <vector>
#include <ftxui/dom/elements.hpp>

class PlaylistPanel : public UIElement {
private:
    DoublyLinkedList<SongNode>* playlist;  // Non-owning pointer
    int selectedIndex;

public:
    PlaylistPanel(DoublyLinkedList<SongNode>* pl)
        : playlist(pl), selectedIndex(0) {}

    int getSelectedIndex() const { return selectedIndex; }

    // ---- Overridden pure virtual methods ----

    ftxui::Element render() override {
        using namespace ftxui;

        if (playlist->isEmpty()) {
            return window(text(" Playlist ") | bold,
                text("  Empty — provide a music directory  ") | center | dim
            );
        }

        std::vector<Element> entries;
        for (int i = 0; i < playlist->getSize(); i++) {
            // operator[] used here to access songs by index
            SongNode& song = (*playlist)[i];

            std::string prefix = (i == selectedIndex) ? " ▸ " : "   ";
            auto entry = text(prefix + song.getTitle() + " - " + song.getArtist());

            if (i == selectedIndex) {
                entry = entry | bold | color(Color::Cyan);
            }
            entries.push_back(entry);
        }

        std::string header = " Playlist (" + std::to_string(playlist->getSize()) + " songs) ";
        return window(text(header) | bold,
            vbox(entries) | vscroll_indicator | frame
                         | size(HEIGHT, LESS_THAN, 20)
        );
    }

    bool handleEvent(ftxui::Event event) override {
        if (playlist->isEmpty()) return false;

        if (event == ftxui::Event::ArrowUp) {
            if (selectedIndex > 0) selectedIndex--;
            return true;
        }
        if (event == ftxui::Event::ArrowDown) {
            if (selectedIndex < playlist->getSize() - 1) selectedIndex++;
            return true;
        }
        return false;
    }

    std::string getName() const override {
        return "Playlist";
    }
};
