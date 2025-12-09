#ifndef CONFIG_H
#define CONFIG_H

#include <QColor>

//can tune speed, colors, screen size, etc. 
namespace Config {

    // --- Display & Screen ---
    constexpr int SCREEN_WIDTH_PX = 480;
    constexpr int SCREEN_HEIGHT_PX = 272;

    // Define the border size
    constexpr int BORDER_SIZE = 32; 

    // Define the playable area dimensions and offsets based on BORDER_SIZE
    constexpr int PLAY_AREA_WIDTH_PX = SCREEN_WIDTH_PX - (2 * (BORDER_SIZE-16)); 
    constexpr int PLAY_AREA_HEIGHT_PX = SCREEN_HEIGHT_PX - (2 * BORDER_SIZE); 
    constexpr int X_OFFSET = BORDER_SIZE - 16; // Adjusted to center the play area
    constexpr int Y_OFFSET = BORDER_SIZE;

    // --- Game Grid & Tile ---
    constexpr int TILE_SIZE_PX = 16;

    // The dimensions of the game board
    constexpr int GRID_COLS = PLAY_AREA_WIDTH_PX / TILE_SIZE_PX; 
    constexpr int GRID_ROWS = PLAY_AREA_HEIGHT_PX / TILE_SIZE_PX; 


    // --- Game Mechanics ---
    constexpr int GAME_TICK_SPEED_MS = 200; // 1000 ms = 1 second


    // --- Visuals & Colors ---
    //Not used anymore (custom images from src file used instead)
    const QColor COLOR_BACKGROUND = Qt::black;
    const QColor COLOR_SNAKE_BODY = Qt::red;
    const QColor COLOR_FOOD = Qt::green;
    const QColor COLOR_SCORE_TEXT = Qt::white;
    const QColor COLOR_GAMEOVER_OVERLAY = QColor(0, 0, 0, 150); // Semi-transparent black
    const QColor COLOR_GAMEOVER_TEXT = Qt::white;

} // namespace Config

#endif // CONFIG_H