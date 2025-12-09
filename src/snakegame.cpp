#include "snakegame.h"
#include <QRandomGenerator>
#include "tonebuzzer.h"

SnakeGame::SnakeGame(int boardWidth, int boardHeight, QObject *parent)
    : QObject(parent),
      m_gameState(Playing),
      m_score(0),
      m_boardWidth(boardWidth),
      m_boardHeight(boardHeight)
{
    //initialize the buzzer
    m_buzzer = new ToneBuzzer("/sys/class/pwm/pwmchip4", this); //pwmchip4 / eHRPWM1A //P9_14
    
    initGame();
}

void SnakeGame::initGame()
{

    // Play the startup sound
    if (m_buzzer) {
        m_buzzer->playStartSound();
    }

    m_gameState = Playing;
    m_direction = Right; //starts direction to the right 
    m_score = 0;
    emit scoreChanged(m_score); //sets score to 0 on new game 

    //make length of 3 snake in center of screen 
    m_snake.clear();
    int startX = m_boardWidth / 2;
    int startY = m_boardHeight / 2;
    m_snake.append(QPoint(startX, startY));
    m_snake.append(QPoint(startX - 1, startY));
    m_snake.append(QPoint(startX - 2, startY));

    placeFood();
}

void SnakeGame::tick()
{
    if (m_gameState == Playing) {
        moveSnake();
        checkCollision();
        emit gameUpdated();
    }
}

void SnakeGame::setDirection(Direction newDirection)
{
    // Prevent the snake from reversing its direction
    if ((m_direction == Up && newDirection == Down) ||
        (m_direction == Down && newDirection == Up) ||
        (m_direction == Left && newDirection == Right) ||
        (m_direction == Right && newDirection == Left)) {
        return;
    }
    m_direction = newDirection;
}

SnakeGame::Direction SnakeGame::getDirection() const
{
    return m_direction;
}

void SnakeGame::togglePause()
{
    if (m_gameState == Playing) {
        m_gameState = Paused;
    } else if (m_gameState == Paused) {
        m_gameState = Playing;
    }
}

const QList<QPoint>& SnakeGame::getSnake() const
{
    return m_snake;
}

const QPoint& SnakeGame::getFood() const
{
    return m_food;
}

int SnakeGame::getScore() const
{
    return m_score;
}

SnakeGame::GameState SnakeGame::getGameState() const
{
    return m_gameState; //playing, paused, gameover, and gamewon
}

void SnakeGame::moveSnake()
{
    QPoint head = m_snake.first();
    QPoint newHead = head;

    switch (m_direction) {
        case Up:
            newHead.ry()--;
            break;
        case Down:
            newHead.ry()++;
            break;
        case Left:
            newHead.rx()--;
            break;
        case Right:
            newHead.rx()++;
            break;
    }

    m_snake.prepend(newHead);
    // The tail is removed unless the snake eats food
    if (newHead != m_food) {
        m_snake.removeLast();
    }
}

void SnakeGame::checkCollision()
{
    QPoint head = m_snake.first();

    // Wall collision
    if (head.x() < 0 || head.x() >= m_boardWidth ||
        head.y() < 0 || head.y() >= m_boardHeight) {
        if (m_buzzer)
            m_buzzer->playCrash();
        m_gameState = GameOver;
        emit gameOver();
        return;
    }

    // Self collision
    for (int i = 1; i < m_snake.size(); ++i) {
        if (head == m_snake.at(i)) {
            if (m_buzzer)
                m_buzzer->playCrash(); 
            m_gameState = GameOver;
            emit gameOver();
            return;
        }
    }

    // Food collision
    if (head == m_food) {
        m_score++;
        emit scoreChanged(m_score);

        // Check if the snake has filled the entire board
        if (m_snake.size() == (m_boardWidth * m_boardHeight)) {
            m_gameState = GameWon;
            emit gameWon();
            // Don't place new food, the board is full.
            return;
        }
         //Mario coin sound
         if (m_buzzer)
             m_buzzer->playCoin();
        placeFood();
    }
}

void SnakeGame::placeFood()
{
    do {
        m_food.setX(QRandomGenerator::global()->bounded(m_boardWidth));
        m_food.setY(QRandomGenerator::global()->bounded(m_boardHeight));
    } while (m_snake.contains(m_food)); // Ensure food doesn't spawn on the snake
}