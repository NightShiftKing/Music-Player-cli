cmake_minimum_required(VERSION 3.14)
project(music-player-cli VERSION 1.0 LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(FetchContent)

# ── FTXUI (Terminal UI Framework) ──────────────────────────
FetchContent_Declare(
    ftxui
    GIT_REPOSITORY https://github.com/ArthurSonzogni/FTXUI.git
    GIT_TAG        v5.0.0
)
FetchContent_MakeAvailable(ftxui)

# ── miniaudio (Cross-Platform Audio) ──────────────────────
# Single-header library — supports WAV, MP3, FLAC, Vorbis
# on Windows, macOS, and Linux with zero dependencies.
FetchContent_Declare(
    miniaudio
    GIT_REPOSITORY https://github.com/mackron/miniaudio.git
    GIT_TAG        0.11.21
    GIT_SHALLOW    TRUE
)
FetchContent_MakeAvailable(miniaudio)

# ── Executable ─────────────────────────────────────────────
add_executable(music-player
    src/main.cpp
    src/DirectoryCrawler.cpp
    src/AudioManager.cpp
    src/PlayerApp.cpp
)

target_link_libraries(music-player
    PRIVATE
        ftxui::screen
        ftxui::dom
        ftxui::component
)

target_include_directories(music-player
    PRIVATE
        src
        ${miniaudio_SOURCE_DIR}
)

# Link platform audio backends
if(WIN32)
    # Windows: miniaudio uses DirectSound/WASAPI (linked automatically)
elseif(APPLE)
    find_library(COREAUDIO_LIB CoreAudio)
    find_library(AUDIOUNIT_LIB AudioUnit)
    find_library(COREFOUNDATION_LIB CoreFoundation)
    target_link_libraries(music-player PRIVATE
        ${COREAUDIO_LIB} ${AUDIOUNIT_LIB} ${COREFOUNDATION_LIB})
else()
    # Linux: link pthreads, dl, m (miniaudio needs these)
    find_package(Threads REQUIRED)
    target_link_libraries(music-player PRIVATE
        Threads::Threads dl m)
endif()

# ── Install ────────────────────────────────────────────────
install(TARGETS music-player DESTINATION bin)
