#pragma once
#include "DoublyLinkedList.h"
#include "SongNode.h"
#include <string>
#include <vector>

// ============================================================
// DirectoryCrawler — Recursively searches directories for audio.
// Demonstrates: Recursion
// ============================================================
class DirectoryCrawler {
private:
    DoublyLinkedList<SongNode>* masterLibrary;
    std::vector<std::string> supportedExtensions;

    // Checks if a file extension is a supported audio format
    bool isSupportedFile(const std::string& extension) const;

public:
    DirectoryCrawler(DoublyLinkedList<SongNode>* library);

    // Recursively search a directory and all subdirectories
    void searchDirectory(const std::string& path);

    int getFilesFound() const;
};
