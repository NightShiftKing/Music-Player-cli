# 🎵 TUI Music Player — Feature Ideas

A prioritized list of potential features and quality-of-life improvements.

---

## 🔥 Cool Features

- [ ] **Shuffle & Repeat Modes** — Toggle between sequential, shuffle, repeat-one, and repeat-all playback
- [ ] **Progress Bar with Seek** — Real-time elapsed/total time bar using `ma_sound_get_cursor_in_seconds()` and `ma_sound_get_length_in_seconds()`; `←/→` seek within a track
- [ ] **Auto-Play Next Song** — Automatically advance to the next track when the current one finishes
- [ ] **Search / Filter** — Press `/` to filter the playlist by title in real time using an FTXUI input component
- [ ] **Album Art (ASCII)** — Render ASCII art from embedded metadata or images found in the music directory
- [ ] **Color Themes** — Cycle through color themes (neon, pastel, monochrome, etc.) with a keypress
- [ ] **Equalizer Visualization** — Animated bar visualization that reacts to playback state

---

## 🛠️ Quality of Life

- [ ] **Remember Last Session** — Save last-used directory and song index to `~/.config/tui-player.conf`
- [ ] **Song Duration Display** — Show track length (e.g., `3:42`) next to each song in the playlist
- [ ] **Playlist Rendering Performance** — Replace O(n²) `operator[]` loop with a cached `std::vector` for display
- [ ] **Jump to Top/Bottom** — `Home`/`End` keys to jump to the first/last song
- [ ] **Now Playing Highlight** — Visually distinguish the currently playing song from the selected cursor (e.g., `♪` marker or different color)
- [ ] **Sort Toggle** — Wire up the `S` key to toggle between sort-by-title, sort-by-artist, sort-by-album
- [ ] **Centered Scroll Window** — Keep the selected item centered in the visible scroll region for large playlists
- [ ] **Graceful Error Handling** — Skip corrupt/unloadable files and auto-advance to the next song
- [ ] **Mouse Support** — Click on songs in the playlist to select and play them (FTXUI supports mouse events)

---

## 🚀 Stretch Goals

- [ ] **ID3 Tag Metadata Parsing** — Use a library like `taglib` to read real artist/album/title from file metadata
- [ ] **Playlist Save/Load** — Export/import playlists as `.m3u` files
- [ ] **Multiple Directory Support** — Accept multiple paths or a config file listing several music directories
- [ ] **Global Hotkeys** — Play/pause from anywhere on the system (platform-specific)
