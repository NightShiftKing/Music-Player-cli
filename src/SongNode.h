#pragma once
#include <string>
#include <iostream>

// ============================================================
// SongNode — Represents a single audio track's metadata.
// Demonstrates: Operator Overloading (<<, ==, <, !=)
// ============================================================
struct SongNode {
    std::string filePath;
    std::string title;
    std::string artist;
    std::string album;

    // Constructor with defaults
    SongNode(const std::string& path = "",
             const std::string& t = "Unknown",
             const std::string& a = "Unknown Artist",
             const std::string& al = "Unknown Album")
        : filePath(path), title(t), artist(a), album(al) {}

    // ---- Operator Overloads (4 total) ----

    // 1. Stream insertion — prints formatted song info
    friend std::ostream& operator<<(std::ostream& os, const SongNode& song) {
        os << song.title << " - " << song.artist << " [" << song.album << "]";
        return os;
    }

    // 2. Equality — two songs are equal if they share the same file path
    bool operator==(const SongNode& other) const {
        return filePath == other.filePath;
    }

    // 3. Inequality
    bool operator!=(const SongNode& other) const {
        return !(*this == other);
    }

    // 4. Less-than — enables sorting by title (alphabetical)
    bool operator<(const SongNode& other) const {
        return title < other.title;
    }
};
