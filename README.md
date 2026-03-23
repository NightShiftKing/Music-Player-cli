# ♪ TUI Music Player

A terminal user interface (TUI) audio player built in C++ using [FTXUI](https://github.com/ArthurSonzogni/FTXUI) and [miniaudio](https://github.com/mackron/miniaudio). Navigate and play local music files through an interactive terminal layout with visual menus, keyboard controls, and real-time playback.

## Features

- **Interactive TUI** — Navigate playlists, control playback, and adjust volume without leaving the terminal
- **Cross-platform audio** — Supports WAV, MP3, and FLAC on Windows, macOS, and Linux
- **Recursive directory scanning** — Automatically discovers all audio files in a folder and its subfolders
- **Keyboard controls** — Play/pause, skip, volume, sort, and quit with simple key bindings

## Prerequisites

| Tool       | Minimum Version | Check Command      |
|------------|----------------|---------------------|
| CMake      | 3.14+          | `cmake --version`   |
| C++ Compiler (GCC/Clang/MSVC) | C++17 support | `g++ --version` |
| Git        | any            | `git --version`     |

> **No libraries to install manually.** FTXUI and miniaudio are downloaded automatically by CMake via FetchContent.

## Build & Run

### Windows (MSYS2 / MinGW)

```bash
cmake -B build -G "MinGW Makefiles"
cmake --build build
.\build\music-player.exe "C:\path\to\your\music"
```

### Linux / macOS

```bash
cmake -B build
cmake --build build
./build/music-player "~/Music"
```

## Controls

| Key         | Action              |
|-------------|---------------------|
| `↑` / `↓`  | Navigate playlist   |
| `Enter`     | Select & play song  |
| `←` / `→`  | Skip backward/forward |
| `Space`     | Play / Pause        |
| `+` / `-`  | Volume up / down    |
| `S`         | Sort playlist       |
| `Q`         | Quit                |

## Project Structure

```
src/
├── main.cpp              Entry point
├── SongNode.h            Song metadata struct (operator overloads)
├── DoublyLinkedList.h    Templated doubly linked list (merge sort)
├── UIElement.h           Abstract base class for UI panels
├── NowPlayingPanel.h     Current song display (inherits UIElement)
├── PlaylistPanel.h       Song list with navigation (inherits UIElement)
├── DirectoryCrawler.h/cpp  Recursive directory scanner
├── AudioManager.h/cpp    Cross-platform audio (miniaudio)
└── PlayerApp.h/cpp       Main application, FTXUI component
```


## Supported Audio Formats

- `.wav` — Waveform Audio
- `.mp3` — MPEG Audio Layer 3
- `.flac` — Free Lossless Audio Codec


