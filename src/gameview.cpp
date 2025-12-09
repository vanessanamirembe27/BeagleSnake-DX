#include "gameview.h"
#include "snakegame.h"
#include "config.h" 
#include <QGraphicsRectItem>
#include <QKeyEvent>
#include <QMouseEvent> 
#include <QGraphicsPixmapItem>

GameView::GameView(SnakeGame *game, QWidget *parent) 
    : QGraphicsView(parent), m_game(game)
{
    m_scene = new QGraphicsScene(0, 0, Config::SCREEN_WIDTH_PX, Config::SCREEN_HEIGHT_PX);
    setScene(m_scene);

    loadSprites();

    // Set the background to black to create the border effect
    setBackgroundBrush(QBrush(m_backgroundPixmap));
    // Remove scroll bars
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    //connectedf the game's update signal to our view's update slot
    connect(m_game, &SnakeGame::gameUpdated, this, &GameView::updateView);

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

    // Get the current direction of the snake
    SnakeGame::Direction currentDirection = m_game->getDirection();

    // Get the position of the tap
    QPoint tapPos = event->pos();

    // Check if the snake is moving horizontally (L or R)
    if (currentDirection == SnakeGame::Left || currentDirection == SnakeGame::Right) {
        // If moving horizontally, the only valid new moves are Up or Down
        if (tapPos.y() < (Config::SCREEN_HEIGHT_PX / 2)) {
            m_game->setDirection(SnakeGame::Up);
        } else {
            // Tap is in the bottom half
            m_game->setDirection(SnakeGame::Down);
        }
    } 
    // Check if the snake is moving vertically (Up or Down)
    else if (currentDirection == SnakeGame::Up || currentDirection == SnakeGame::Down) {
        // If moving vertically, the only valid new moves are Left or Right
        if (tapPos.x() < (Config::SCREEN_WIDTH_PX / 2)) {
            m_game->setDirection(SnakeGame::Left);
        } else {
            // Tap is in the right half
            m_game->setDirection(SnakeGame::Right);
        }
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
    QPoint foodPos = m_game->getFood();

    // Create a pixmap item for the food sprite
    QGraphicsPixmapItem *foodItem = new QGraphicsPixmapItem(m_foodPixmap.scaled(Config::TILE_SIZE_PX, Config::TILE_SIZE_PX, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    
    // Set its position using the offsets
    foodItem->setPos((foodPos.x() * Config::TILE_SIZE_PX) + Config::X_OFFSET,
                     (foodPos.y() * Config::TILE_SIZE_PX) + Config::Y_OFFSET);

    m_scene->addItem(foodItem);
}

void GameView::loadSprites()
{
    // Load background
    m_backgroundPixmap = QPixmap(":/icons/grass.png");

    // Load Food
    m_foodPixmap = QPixmap(":/icons/beagle.png");

    // Load Head
    m_headUp = QPixmap(":/icons/snakeheadup.png");
    m_headDown = QPixmap(":/icons/snakeheaddown.png");
    m_headLeft = QPixmap(":/icons/snakeheadleft.png");
    m_headRight = QPixmap(":/icons/snakeheadright.png");

    // Load Tongue
    m_tongueUp = QPixmap(":/icons/snaketongueup.png");
    m_tongueDown = QPixmap(":/icons/snaketonguedown.png");
    m_tongueLeft = QPixmap(":/icons/snaketongueleft.png");
    m_tongueRight = QPixmap(":/icons/snaketongueright.png");

    // Load Body (now four directions)
    m_bodyUp = QPixmap(":/icons/snakebodyup.png");
    m_bodyDown = QPixmap(":/icons/snakebodydown.png");
    m_bodyLeft = QPixmap(":/icons/snakebodyleft.png");
    m_bodyRight = QPixmap(":/icons/snakebodyright.png");

    // Load Tail
    m_tailUp = QPixmap(":/icons/snaketailup.png");
    m_tailDown = QPixmap(":/icons/snaketaildown.png");
    m_tailLeft = QPixmap(":/icons/snaketailleft.png");
    m_tailRight = QPixmap(":/icons/snaketailright.png");

    // Load Turns (From->To)
    m_turnUL = QPixmap(":/icons/snaketurnupleft.png");
    m_turnUR = QPixmap(":/icons/snaketurnupright.png");
    m_turnLU = QPixmap(":/icons/snaketurnleftup.png");
    m_turnRU = QPixmap(":/icons/snaketurnrightup.png");
    m_turnLD = QPixmap(":/icons/snaketurnleftdown.png");
    m_turnRD = QPixmap(":/icons/snaketurnrightdown.png");
    m_turnDL = QPixmap(":/icons/snaketurndownleft.png");
    m_turnDR = QPixmap(":/icons/snaketurndownright.png");
}

void GameView::drawSnake()
{
    const QList<QPoint>& snakeBody = m_game->getSnake();
    if (snakeBody.isEmpty()) {
        return;
    }

    // --- Draw Head ---
    const QPoint& headPos = snakeBody.first();
    QPixmap headPixmap;
    switch (m_game->getDirection()) {
        case SnakeGame::Up:    headPixmap = m_headUp;    break;
        case SnakeGame::Down:  headPixmap = m_headDown;  break;
        case SnakeGame::Left:  headPixmap = m_headLeft;  break;
        case SnakeGame::Right: headPixmap = m_headRight; break;
    }
    QGraphicsPixmapItem *headItem = new QGraphicsPixmapItem(headPixmap.scaled(Config::TILE_SIZE_PX, Config::TILE_SIZE_PX, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    // Apply offsets to the position
    headItem->setPos((headPos.x() * Config::TILE_SIZE_PX) + Config::X_OFFSET, 
                     (headPos.y() * Config::TILE_SIZE_PX) + Config::Y_OFFSET);
    m_scene->addItem(headItem);

    // --- Draw Tongue --- (tongue allows for more intuitive display without unexepcted wall crashing)
    QPoint tongueGridPos = headPos;
    QPixmap tonguePixmap;
    switch (m_game->getDirection()) {
        case SnakeGame::Up:    tongueGridPos.ry()--; tonguePixmap = m_tongueUp; break;
        case SnakeGame::Down:  tongueGridPos.ry()++; tonguePixmap = m_tongueDown; break;
        case SnakeGame::Left:  tongueGridPos.rx()--; tonguePixmap = m_tongueLeft; break;
        case SnakeGame::Right: tongueGridPos.rx()++; tonguePixmap = m_tongueRight; break;
    }
    QGraphicsPixmapItem *tongueItem = new QGraphicsPixmapItem(tonguePixmap.scaled(Config::TILE_SIZE_PX, Config::TILE_SIZE_PX, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    tongueItem->setPos((tongueGridPos.x() * Config::TILE_SIZE_PX) + Config::X_OFFSET,
                       (tongueGridPos.y() * Config::TILE_SIZE_PX) + Config::Y_OFFSET);
    m_scene->addItem(tongueItem);

    // --- Draw Body Segments ---
    for (int i = 1; i < snakeBody.size() - 1; ++i) {
        const QPoint& prev = snakeBody.at(i - 1); // Segment toward the head
        const QPoint& curr = snakeBody.at(i);     // Current segment
        const QPoint& next = snakeBody.at(i + 1); // Segment toward the tail

        QPixmap bodyPixmap;
        // Check if it's a straight piece
        if ((prev.x() == curr.x() && curr.x() == next.x()) || (prev.y() == curr.y() && curr.y() == next.y())) {
            if (prev.y() > curr.y()) {
                bodyPixmap = m_bodyDown; // Moving down
            } else if (prev.y() < curr.y()) {
                bodyPixmap = m_bodyUp; // Moving up
            } else if (prev.x() > curr.x()) {
                bodyPixmap = m_bodyRight; // Moving right
            } else {
                bodyPixmap = m_bodyLeft; // Moving left
            }
        } else { // It's a turn

            // Determine the direction FROM the tail-side segment (next) TO the current segment (curr)
            bool came_from_up = curr.y() < next.y();
            bool came_from_down = curr.y() > next.y();
            bool came_from_right = curr.x() > next.x();
            bool came_from_left = curr.x() < next.x();

            // Determine the direction FROM the current segment (curr) TO the head-side segment (prev)
            bool going_to_up = prev.y() < curr.y();
            bool going_to_down = prev.y() > curr.y();
            bool going_to_right = prev.x() > curr.x();
            bool going_to_left = prev.x() < curr.x();

            // Select the correct turn sprite based on the specific from/to combination
            if (came_from_up && going_to_left) {
                bodyPixmap = m_turnUL; // Came from Up, going to Left
            } else if (came_from_up && going_to_right) {
                bodyPixmap = m_turnUR; // Came from Up, going to Right
            } else if (came_from_down && going_to_left) {
                bodyPixmap = m_turnDL; // Came from Down, going to Left
            } else if (came_from_down && going_to_right) {
                bodyPixmap = m_turnDR; // Came from Down, going to Right
            } else if (came_from_left && going_to_up) {
                bodyPixmap = m_turnLU; // Came from Left, going to Up
            } else if (came_from_left && going_to_down) {
                bodyPixmap = m_turnLD; // Came from Left, going to Down
            } else if (came_from_right && going_to_up) {
                bodyPixmap = m_turnRU; // Came from Right, going to Up
            } else if (came_from_right && going_to_down) {
                bodyPixmap = m_turnRD; // Came from Right, going to Down
            }
        }
        QGraphicsPixmapItem *bodyItem = new QGraphicsPixmapItem(bodyPixmap.scaled(Config::TILE_SIZE_PX, Config::TILE_SIZE_PX, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
        bodyItem->setPos((curr.x() * Config::TILE_SIZE_PX) + Config::X_OFFSET, 
                         (curr.y() * Config::TILE_SIZE_PX) + Config::Y_OFFSET);
        m_scene->addItem(bodyItem);
    }

    // --- Draw Tail ---
    const QPoint& tailPos = snakeBody.last();
    const QPoint& beforeTail = snakeBody.at(snakeBody.size() - 2);
    QPixmap tailPixmap;
    if (beforeTail.y() < tailPos.y()) { // Segment before is above, so tail points up
        tailPixmap = m_tailUp;
    } else if (beforeTail.y() > tailPos.y()) { // Segment before is below, so tail points down
        tailPixmap = m_tailDown;
    } else if (beforeTail.x() < tailPos.x()) { // Segment before is to the left, so tail points left
        tailPixmap = m_tailLeft;
    } else { // Segment before is to the right, so tail points right
        tailPixmap = m_tailRight;
    }
    QGraphicsPixmapItem *tailItem = new QGraphicsPixmapItem(tailPixmap.scaled(Config::TILE_SIZE_PX, Config::TILE_SIZE_PX, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    tailItem->setPos((tailPos.x() * Config::TILE_SIZE_PX) + Config::X_OFFSET, 
                     (tailPos.y() * Config::TILE_SIZE_PX) + Config::Y_OFFSET);
    m_scene->addItem(tailItem);
}