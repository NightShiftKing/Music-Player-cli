#include "DirectoryCrawler.h"
#include <filesystem>
#include <algorithm>
#include <iostream>

namespace fs = std::filesystem;

DirectoryCrawler::DirectoryCrawler(DoublyLinkedList<SongNode>* library)
    : masterLibrary(library) {
    // Audio formats that the player can load
    supportedExtensions = {".wav", ".mp3", ".flac", ".ogg"};
}

bool DirectoryCrawler::isSupportedFile(const std::string& extension) const {
    std::string ext = extension;
    // Normalize to lowercase for case-insensitive comparison
    std::transform(ext.begin(), ext.end(), ext.begin(), ::tolower);
    for (const auto& supported : supportedExtensions) {
        if (ext == supported) return true;
    }
    return false;
}

// ============================================================
// RECURSION: Walks the directory tree. For each subdirectory
// found, searchDirectory calls itself (recursive call).
// For each supported audio file found, a SongNode is created
// and inserted into the master library (doubly linked list).
// ============================================================
void DirectoryCrawler::searchDirectory(const std::string& path) {
    try {
        for (const auto& entry : fs::directory_iterator(path)) {
            if (entry.is_directory()) {
                // *** RECURSIVE CALL — descend into subdirectory ***
                searchDirectory(entry.path().string());
            }
            else if (entry.is_regular_file()) {
                std::string ext = entry.path().extension().string();
                if (isSupportedFile(ext)) {
                    std::string filePath = entry.path().string();
                    std::string title    = entry.path().stem().string();
                    std::string album    = entry.path().parent_path()
                                               .filename().string();

                    SongNode song(filePath, title, "Unknown Artist", album);
                    masterLibrary->insertNode(song);
                }
            }
        }
    } catch (const fs::filesystem_error& e) {
        // Graceful error handling for permission issues, etc.
        std::cerr << "Error accessing: " << path
                  << " — " << e.what() << std::endl;
    }
}

int DirectoryCrawler::getFilesFound() const {
    return masterLibrary->getSize();
}
