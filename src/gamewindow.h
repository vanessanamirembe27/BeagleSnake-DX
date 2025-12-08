#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QWidget>

// Forward-declarations for pointer members
class QStackedWidget;
class QLabel;
class QPushButton;
class GameView;
class SnakeGame;
class QTimer;

class GameWindow : public QWidget // Changed from QMainWindow to QWidget
{
    Q_OBJECT

public:
    explicit GameWindow(QWidget *parent = nullptr);
    ~GameWindow();

private slots:
    // Screen navigation
    void startGame();
    void showMenu();

    // Game state handling
    void handleGameOver();
    void handleGameWon();
    void pauseGame();   
    void resumeGame();  
    void restartGame();
    void updateScore(int score);

private:
    // Functions to build each screen
    void createMenuScreen();
    void createGameScreen();
    void createPauseScreen(); 
    void createGameOverScreen();
    void connectSignals();

    // Core components
    SnakeGame *m_game;
    GameView *m_view;
    QTimer *m_timer;

    // Screen management
    QStackedWidget *m_stack;
    QWidget *m_menuScreen;
    QWidget *m_gameScreen;
    QWidget *m_pauseScreen;
    QWidget *m_gameOverScreen;

    // High score tracking
    int m_highScore = 0;

    // --- UI Elements ---
    // Menu Screen
    QLabel *m_highScoreLabel_menu;

    // Game Screen
    QLabel *m_scoreLabel_game;
    QPushButton *m_pauseButton;

    // Game Over Screen
    QLabel *m_gameOverTitle_gameOver; 
    QLabel *m_finalScoreLabel_gameOver;
    QLabel *m_highScoreLabel_gameOver;
};

#endif // GAMEWINDOW_H