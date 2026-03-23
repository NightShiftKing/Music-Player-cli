// ============================================================
// File: PlayerApp.h
// Author: Michael Monreal
// Description: Declares the PlayerApp class which serves as
//              the main application. Owns the playlist, audio
//              manager, and UI panels. Composes all components
//              into an interactive FTXUI terminal interface.
//              Demonstrates: Composition, Polymorphism.
// ============================================================
#pragma once
#include "DoublyLinkedList.h"
#include "SongNode.h"
#include "UIElement.h"
#include "NowPlayingPanel.h"
#include "PlaylistPanel.h"
#include "AudioManager.h"
#include <vector>
#include <memory>

class PlayerApp {
private:
    DoublyLinkedList<SongNode> playlist;
    AudioManager audioManager;

    // Polymorphic panel storage — base class pointers (UIElement*)
    std::vector<std::unique_ptr<UIElement>> panels;

    // Non-owning convenience pointers for direct access
    NowPlayingPanel* nowPlayingPtr;
    PlaylistPanel*   playlistPtr;

    void loadAndPlayCurrent();

public:
    PlayerApp();
    ~PlayerApp();

    DoublyLinkedList<SongNode>& getPlaylist();
    void run();
};
