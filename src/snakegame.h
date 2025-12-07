#ifndef SNAKEGAME_H
#define SNAKEGAME_H

#include <QObject>
#include <QList>
#include <QPoint>

class ToneBuzzer;

class SnakeGame : public QObject
{
    Q_OBJECT
public:
    explicit SnakeGame(int boardWidth, int boardHeight, QObject *parent = nullptr);

    enum Direction {
        Up,
        Down,
        Left,
        Right
    };

    enum GameState {
        Playing,
        Paused,
        GameOver,
        GameWon 
    };



    void initGame();
    void tick();
    void setDirection(Direction newDirection);
    Direction getDirection() const;
    void togglePause(); 

    const QList<QPoint>& getSnake() const;
    const QPoint& getFood() const;
    int getScore() const;
    GameState getGameState() const;

signals:
    void gameUpdated();
    void scoreChanged(int score);
    void gameOver();
    void gameWon();

private:
    void moveSnake();
    void checkCollision();
    void placeFood();

    QList<QPoint> m_snake;
    QPoint m_food;
    Direction m_direction;
    GameState m_gameState;
    int m_score;

    const int m_boardWidth;
    const int m_boardHeight;
    ToneBuzzer *m_buzzer;

};

#endif // SNAKEGAME_H