#include "DoublyLinkedList.h"
#include "SongNode.h"
#include "DirectoryCrawler.h"
#include "PlayerApp.h"
#include <iostream>
#include <string>
#include <filesystem>

int main(int argc, char* argv[]) {
    std::string musicPath;

    // Accept path as command-line argument or prompt the user
    if (argc > 1) {
        musicPath = argv[1];
    } else {
        std::cout << "\n";
        std::cout << "+======================================+\n";
        std::cout << "|     ♪  TUI Music Player  ♪          |\n";
        std::cout << "+======================================+\n\n";
        std::cout << "Enter path to your music folder: ";
        std::getline(std::cin, musicPath);
    }

    // ---- Validate the provided path ----
    if (!std::filesystem::exists(musicPath)) {
        std::cerr << "Error: Directory '" << musicPath
                  << "' does not exist.\n";
        return 1;
    }
    if (!std::filesystem::is_directory(musicPath)) {
        std::cerr << "Error: '" << musicPath
                  << "' is not a directory.\n";
        return 1;
    }

    // ---- Build the player ----
    PlayerApp app;

    // Use the recursive DirectoryCrawler to find audio files
    DirectoryCrawler crawler(&app.getPlaylist());

    std::cout << "Scanning '" << musicPath << "' for audio files...\n";
    crawler.searchDirectory(musicPath);   // << RECURSION happens here

    if (app.getPlaylist().isEmpty()) {
        std::cerr << "No supported audio files found in '"
                  << musicPath << "'.\n";
        std::cerr << "Supported formats: .wav, .mp3, .flac, .ogg\n";
        return 1;
    }

    std::cout << "Found " << crawler.getFilesFound() << " audio file(s).\n";

    // Sort the playlist alphabetically by title (Merge Sort)
    std::cout << "Sorting playlist...\n";
    app.getPlaylist().sort();   // << MERGE SORT happens here

    // Print the playlist to stdout before launching TUI
    std::cout << "\nPlaylist:\n" << app.getPlaylist() << std::endl;

    std::cout << "Launching player... (press Q to quit)\n";

    // Run the interactive TUI
    app.run();

    std::cout << "Goodbye!\n";
    return 0;
}
