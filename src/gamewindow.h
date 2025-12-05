#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QPushButton>

class GameView;
class SnakeGame;
class QTimer;

class GameWindow : public QMainWindow
{
    Q_OBJECT

public:
    GameWindow(QWidget *parent = nullptr);
    ~GameWindow();

private slots:
    void handleGameOver();
    void restartGame();
    void updateScore(int score);

private:
    void createGameOverWidgets();

    SnakeGame *m_game;
    GameView *m_view;
    QTimer *m_timer;

    // Game Over overlay widgets
    QWidget *m_gameOverWidget;
    QLabel *m_scoreLabel;
    QPushButton *m_restartButton;
};

#endif // GAMEWINDOW_H