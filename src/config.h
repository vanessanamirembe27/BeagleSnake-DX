#ifndef CONFIG_H
#define CONFIG_H

#include <QColor>

//can tune speed, colors, screen size, etc. here --------------------------------------------

// Use a namespace to group all configuration constants and avoid polluting the global scope.
namespace Config {

    // --- Display & Screen ---
    // Physical screen dimensions in pixels for the 4.3" LCD cape.
    constexpr int SCREEN_WIDTH_PX = 480;
    constexpr int SCREEN_HEIGHT_PX = 272;

    // Define the playable area dimensions and offsets for centering
    constexpr int PLAY_AREA_WIDTH_PX = 448;
    constexpr int PLAY_AREA_HEIGHT_PX = 240;
    constexpr int X_OFFSET = (SCREEN_WIDTH_PX - PLAY_AREA_WIDTH_PX) / 2; // (480 - 448) / 2 = 16
    constexpr int Y_OFFSET = (SCREEN_HEIGHT_PX - PLAY_AREA_HEIGHT_PX) / 2; // (272 - 240) / 2 = 16


    // --- Game Grid & Tile ---
    // The size of a single game tile (e.g., a snake segment) in pixels.
    // Choose a value that divides evenly into the screen dimensions.
    constexpr int TILE_SIZE_PX = 16;

    // The dimensions of the game board in grid units (columns and rows).
    // These are now calculated from the smaller playable area.
    constexpr int GRID_COLS = PLAY_AREA_WIDTH_PX / TILE_SIZE_PX; 
    constexpr int GRID_ROWS = PLAY_AREA_HEIGHT_PX / TILE_SIZE_PX; 


    // --- Game Mechanics ---
    // The speed of the game, representing the delay between ticks in milliseconds.
    // A lower value makes the game faster.
    constexpr int GAME_TICK_SPEED_MS = 200; // 1000 ms = 1 second


    // --- Visuals & Colors ---
    // Define all game colors here for easy theming.
    const QColor COLOR_BACKGROUND = Qt::black;
    const QColor COLOR_SNAKE_BODY = Qt::red;
    const QColor COLOR_FOOD = Qt::green;
    const QColor COLOR_SCORE_TEXT = Qt::white;
    const QColor COLOR_GAMEOVER_OVERLAY = QColor(0, 0, 0, 150); // Semi-transparent black
    const QColor COLOR_GAMEOVER_TEXT = Qt::white;

} // namespace Config

#endif // CONFIG_H