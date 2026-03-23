# ♪ TUI Music Player

A terminal user interface (TUI) audio player built in C++ using [FTXUI](https://github.com/ArthurSonzogni/FTXUI) and [miniaudio](https://github.com/mackron/miniaudio). Navigate and play local music files through an interactive terminal layout with visual menus, keyboard controls, and real-time playback.

## Features

- **Interactive TUI** — Navigate playlists, control playback, and adjust volume without leaving the terminal
- **Cross-platform audio** — Supports WAV, MP3, and FLAC on Windows, macOS, and Linux
- **Recursive directory scanning** — Automatically discovers all audio files in a folder and its subfolders
- **Keyboard controls** — Play/pause, skip, volume, sort, and quit with simple key bindings

## Installation

### Homebrew (macOS / Linux)

```bash
brew tap NightShiftKing/tap
brew install music-player-cli
```

### Quick Install Script (Linux / macOS)

```bash
curl -fsSL https://raw.githubusercontent.com/NightShiftKing/Music-Player-cli/main/install.sh | bash
```

This auto-detects your OS, downloads the latest binary, and installs it to `~/.local/bin`.

### Manual Download

Download the latest binary for your platform from the [Releases page](https://github.com/NightShiftKing/Music-Player-cli/releases):

| Platform | File |
|----------|------|
| Linux | `music-player-linux-amd64.tar.gz` |
| macOS | `music-player-macos-amd64.tar.gz` |
| Windows | `music-player-windows-amd64.zip` |

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

## Contributing

We welcome contributions! Please see [CONTRIBUTING.md](file:///home/nightshiftking/Documents/Music-Player-cli/CONTRIBUTING.md) and the [Code of Conduct](file:///home/nightshiftking/Documents/Music-Player-cli/CODE_OF_CONDUCT.md) for details on how to get involved.

## License

This project is licensed under the MIT License - see the [LICENSE](file:///home/nightshiftking/Documents/Music-Player-cli/LICENSE) file for details.


