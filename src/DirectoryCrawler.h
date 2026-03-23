// ============================================================
// File: DirectoryCrawler.h
// Author: Michael Monreal
// Description: Declares the DirectoryCrawler class which
//              recursively searches a directory tree for
//              supported audio files and inserts them into
//              a doubly linked list in sorted order.
//              Demonstrates: Recursion.
// ============================================================
#pragma once
#include "DoublyLinkedList.h"
#include "SongNode.h"
#include <string>
#include <vector>

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
