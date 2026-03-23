My capstone project will be a terminal user interface (TUI) audio player. The
program will allow users to navigate and play local music files through an interactive
layout with visual menus, rather than a standard command-line prompt. It is intended for
users who want a minimalist way to listen to music in a terminal workflow without
switching windows or using a heavy GUI application. This program is useful because it
combines file management with real-time audio control in a highly visual way. The user
will enter file paths to their music, and the program will extract metadata or allow for
manual entry. Users will interact with the program by navigating a menu using arrow
keys or mouse clicks to play, skip, or adjust the volume while the program tracks the
playback state in a persistent header.

A major challenge will be concurrency, ensuring the audio plays in the
background while the TUI continues to refresh the time elapsed bar and listen for new
user input. To achieve this, I will use SDL2's built-in audio callback system, which
manages audio streaming on a dedicated thread without requiring manual thread
management. This lets the TUI event loop and audio playback run concurrently while
avoiding the complexity of raw `std::thread` synchronization. I will also need to handle
the logic of linking the song nodes to the actual file paths on the hard drive to ensure
the correct file is loaded. Managing the TUI layout while manipulating playlist pointers
will also be complex.

For the user interface, I will use the FTXUI library, which provides an abstract
base class, `ComponentBase`, that defines how visual components are rendered and how
they handle events. My main `PlayerApp` class will inherit from `ComponentBase` and
override its `Render()` method to define the visual layout and its `OnEvent()` method to
handle keyboard and mouse input. This allows polymorphic dispatch, so the FTXUI
framework can call `Render()` and `OnEvent()` on any component and execute the
correct logic based on the object type. Within the player, the UI will be composed of
elements such as song list displays, a progress bar, and playback controls.

For the playlist, I will implement a doubly linked list from scratch. This is a more
advanced data structure than standard arrays or vectors and is necessary to traverse
songs both forward and backward using pointers. Each `SongNode` in the list will store
the file path, title, and pointers to the next and previous nodes. Additional metadata
fields such as artist, album, and duration may be added as the project evolves.

Finally, I will use recursion for a directory crawler. When a user provides a music
folder, a recursive function will search through all subfolders to find and link every
supported audio file to the master library. The program will handle edge cases
gracefully, including invalid or empty directory paths, directories containing no
supported audio files, audio files that fail to load during playback, and attempts to
skip when the playlist is empty or at its boundary.

Stretch goals for the project include shuffle mode, search and filter
functionality, and the ability to save and load playlists, though the core deliverable
focuses on play, pause, skip, and volume control within a polished TUI.