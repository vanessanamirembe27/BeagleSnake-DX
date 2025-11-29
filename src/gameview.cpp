#include "gameview.h"
#include "snakegame.h"
#include "config.h" 
#include <QGraphicsRectItem>
#include <QKeyEvent>
#include <QMouseEvent> 

GameView::GameView(QWidget *parent) : QGraphicsView(parent)
{
    // Set up the scene with pixel dimensions
    m_scene = new QGraphicsScene(0, 0, Config::SCREEN_WIDTH_PX, Config::SCREEN_HEIGHT_PX);
    setScene(m_scene);

    // 1. Create an instance of the game logic
    m_game = new SnakeGame(Config::GRID_COLS, Config::GRID_ROWS, this);
    
    // 2. Connect the game's update signal to our view's update slot
    connect(m_game, &SnakeGame::gameUpdated, this, &GameView::updateView);

    //set up timer to drive game 
    m_timer = new QTimer(this); 
    connect(m_timer, &QTimer::timeout, m_game, &SnakeGame::tick); 
    m_timer->start(Config::GAME_TICK_SPEED_MS); // updates every 150 ms 

    // Initial draw
    updateView();
}

void GameView::keyPressEvent(QKeyEvent *event) 
{ 
    switch (event->key()){ 
        case Qt::Key_Up: 
            m_game->setDirection(SnakeGame::Up); 
            break; 
        case Qt::Key_Down:
            m_game->setDirection(SnakeGame::Down); 
            break; 
        case Qt::Key_Left: 
            m_game->setDirection(SnakeGame::Left);
            break;
        case Qt::Key_Right: 
            m_game->setDirection(SnakeGame::Right); 
            break; 
        default: 
            QGraphicsView::keyPressEvent(event);    
    }
}

void GameView::mousePressEvent(QMouseEvent *event)
{
    // Get the position of the tap
    QPoint tapPos = event->pos();

    // Define the boundaries for the control regions (dividing the screen into thirds)
    int thirdWidth = Config::SCREEN_WIDTH_PX / 3;
    int thirdHeight = Config::SCREEN_HEIGHT_PX / 3;

    // Check which region the tap is in
    if (tapPos.y() < thirdHeight) {
        // Top region
        m_game->setDirection(SnakeGame::Up);
    } else if (tapPos.y() > (2 * thirdHeight)) {
        // Bottom region
        m_game->setDirection(SnakeGame::Down);
    } else if (tapPos.x() < thirdWidth) {
        // Left region (and not top or bottom)
        m_game->setDirection(SnakeGame::Left);
    } else if (tapPos.x() > (2 * thirdWidth)) {
        // Right region (and not top or bottom)
        m_game->setDirection(SnakeGame::Right);
    } else {
        // Center region, do nothing or maybe pause the game
        // m_game->togglePause(); // Optional: tapping the center pauses (if not implemented in gamewindow.cpp/.h)
    }

    // Call the base class implementation
    QGraphicsView::mousePressEvent(event);
}

// This function is called every time the game state changes
void GameView::updateView()
{
    // Clear the old items from the scene
    m_scene->clear();

    // Draw the food and snake in their new positions
    drawFood();
    drawSnake();
}

void GameView::drawFood()
{
    // 3. Get the food's grid position from the game logic
    QPoint foodPos = m_game->getFood();

    // 4. Draw a rectangle for the food at the correct pixel position
    QGraphicsRectItem *foodItem = new QGraphicsRectItem(
        foodPos.x() * Config::TILE_SIZE_PX,
        foodPos.y() * Config::TILE_SIZE_PX,
        Config::TILE_SIZE_PX,
        Config::TILE_SIZE_PX
    );
    foodItem->setBrush(Config::COLOR_FOOD); // Make the food red
    m_scene->addItem(foodItem);
}

void GameView::drawSnake()
{
    const QList<QPoint>& snakeBody = m_game->getSnake();
    for (const QPoint& segment : snakeBody) {
        QGraphicsRectItem *segmentItem = new QGraphicsRectItem(
            segment.x() * Config::TILE_SIZE_PX,
            segment.y() * Config::TILE_SIZE_PX,
            Config::TILE_SIZE_PX,
            Config::TILE_SIZE_PX
        );
        segmentItem->setBrush(Config::COLOR_SNAKE_BODY); // Make the snake green
        m_scene->addItem(segmentItem);
    }
}