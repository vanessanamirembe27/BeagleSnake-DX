#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QTimer> 

class SnakeGame; // Forward declaration

class GameView : public QGraphicsView
{
    Q_OBJECT
public:
    GameView(QWidget *parent = nullptr);

public slots:
    void updateView(); // This slot will be connected to the game's gameUpdated signal

protected: 
    void keyPressEvent(QKeyEvent *event) override; //override virtual function from base class check
    void mousePressEvent(QMouseEvent *event) override; //touchscreen support + override virtual function from base class check 

private:
    void drawGame();
    void drawFood();
    void drawSnake();

    QGraphicsScene *m_scene; //scene instance 
    SnakeGame *m_game; // The game logic instance
    QTimer *m_timer;

    // We need to decide the size of each grid cell in pixels
    const int m_cellSize = 16; //16 x 16 pixel cells 
};

#endif // GAMEVIEW_H
