#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QTimer> 
#include <QPixmap> //added for image support 

class SnakeGame; // Forward declaration

class GameView : public QGraphicsView
{
    Q_OBJECT
public:
    GameView(SnakeGame *game, QWidget *parent = nullptr); //consturctor takes pointer to game logic

public slots:
    void updateView(); // This slot will be connected to the game's gameUpdated signal

protected: 
    void keyPressEvent(QKeyEvent *event) override; //override virtual function from base class check
    void mousePressEvent(QMouseEvent *event) override; //touchscreen support + override virtual function from base class check 

private:
    void drawFood();
    void drawSnake();
    void loadSnakeSprites(); //load snake images 

    QGraphicsScene *m_scene; //scene instance 
    SnakeGame *m_game; // The game logic instance pointer (not owner)

    QPixmap m_headUp, m_headDown, m_headLeft, m_headRight;
    QPixmap m_tongueUp, m_tongueDown, m_tongueLeft, m_tongueRight;

    QPixmap m_bodyUp, m_bodyDown, m_bodyLeft, m_bodyRight; 

    QPixmap m_tailUp, m_tailDown, m_tailLeft, m_tailRight;

    QPixmap m_turnUL, m_turnUR, m_turnLU, m_turnLD, m_turnRU, m_turnRD, m_turnDL, m_turnDR;

    //ABSOLETE NOW- moved to config.h 
    // We need to decide the size of each grid cell in pixels
    //const int m_cellSize = 16; //16 x 16 pixel cells 
};

#endif // GAMEVIEW_H
