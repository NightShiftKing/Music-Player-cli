#pragma once
#include "DoublyLinkedList.h"
#include "SongNode.h"
#include "UIElement.h"
#include "NowPlayingPanel.h"
#include "PlaylistPanel.h"
#include "AudioManager.h"
#include <vector>
#include <memory>

// ============================================================
// PlayerApp — Main application, ties all components together.
// Demonstrates: Composition, Polymorphism (UIElement* dispatch)
// ============================================================
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
