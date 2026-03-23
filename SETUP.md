# TUI Music Player — Setup & Build Guide

## Prerequisites

You need the following installed on your system:

| Tool        | Minimum Version | How to Check       |
|-------------|----------------|--------------------|
| **CMake**   | 3.14+          | `cmake --version`  |
| **G++ (GCC)** | 8+ (C++17)  | `g++ --version`    |
| **Git**     | any            | `git --version`    |

> **Note:** FTXUI and miniaudio are downloaded automatically by CMake (via FetchContent).
> You do NOT need to install any libraries manually.

## Building the Project

### Windows (PowerShell)

```powershell
# 1. Configure (first run downloads FTXUI + miniaudio)
cmake -B build -G "MinGW Makefiles"

# 2. Build
cmake --build build
```

### Linux / macOS

```bash
cmake -B build
cmake --build build
```

The executable will be at `build/music-player.exe` (Windows) or `build/music-player` (Linux/macOS).

## Running the Player

```bash
# Option A: Launch and type the path when prompted
./build/music-player.exe

# Option B: Pass the music folder as a command-line argument
./build/music-player.exe "C:/Users/YourName/Music"
```

### Controls

| Key         | Action              |
|-------------|---------------------|
| `↑` / `↓`  | Navigate playlist   |
| `Enter`     | Select & play song  |
| `←` / `→`  | Skip backward/forward |
| `Space`     | Play / Pause        |
| `+` / `-`   | Volume up / down    |
| `S`         | Sort playlist       |
| `Q`         | Quit                |

## Supported Audio Formats

All formats are natively supported on Windows, macOS, and Linux:

- `.wav` — Waveform Audio
- `.mp3` — MPEG Audio Layer 3
- `.flac` — Free Lossless Audio Codec

## Project Structure

```
music-player-cli/
├── CMakeLists.txt            # Build config (FetchContent for FTXUI + miniaudio)
├── SETUP.md                  # This file
├── capstone_proposal.md      # Project proposal
├── src/
│   ├── main.cpp              # Entry point
│   ├── SongNode.h            # Song data struct (operator overloads)
│   ├── DoublyLinkedList.h    # Template linked list (merge sort)
│   ├── UIElement.h           # Abstract base class
│   ├── NowPlayingPanel.h     # Inherits UIElement
│   ├── PlaylistPanel.h       # Inherits UIElement
│   ├── DirectoryCrawler.h    # Recursive directory search (header)
│   ├── DirectoryCrawler.cpp  # Recursive directory search (impl)
│   ├── AudioManager.h        # Audio manager (header)
│   ├── AudioManager.cpp      # Audio manager (impl, uses miniaudio)
│   ├── PlayerApp.h           # Main app (header)
│   └── PlayerApp.cpp         # Main app (impl)
└── build/                    # Generated build files
```

## Troubleshooting

### CMake can't find a generator (Windows)
Make sure you pass `-G "MinGW Makefiles"` (case-sensitive). Run from the
MSYS2 UCRT64 terminal, or ensure MinGW's `bin` directory is on your system PATH.

### No audio output
- Make sure your music folder contains `.wav`, `.mp3`, or `.flac` files.
- Press `Enter` on a song in the playlist to select and play it.
- Try pressing `+` to increase the volume.
