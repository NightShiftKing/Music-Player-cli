// ============================================================
// File: SongNode.h
// Author: Michael Monreal
// Description: Defines the SongNode class which stores metadata
//              for a single audio track. Demonstrates information
//              hiding with private members and public getters/setters,
//              as well as operator overloading (<<, ==, !=, <).
// ============================================================
#pragma once
#include <string>
#include <iostream>

class SongNode {
private:
    // Private member variables (information hiding)
    std::string filePath;
    std::string title;
    std::string artist;
    std::string album;

public:
    // Constructor with default values
    SongNode(const std::string& path = "",
             const std::string& t = "Unknown",
             const std::string& a = "Unknown Artist",
             const std::string& al = "Unknown Album")
        : filePath(path), title(t), artist(a), album(al) {}

    // --- Getters (public access to private data) ---
    std::string getFilePath() const { return filePath; }
    std::string getTitle()    const { return title; }
    std::string getArtist()   const { return artist; }
    std::string getAlbum()    const { return album; }

    // --- Setters ---
    void setTitle(const std::string& t)  { title = t; }
    void setArtist(const std::string& a) { artist = a; }
    void setAlbum(const std::string& al) { album = al; }

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

    // 4. Less-than — enables sorted insertion by title (alphabetical)
    bool operator<(const SongNode& other) const {
        return title < other.title;
    }
};
