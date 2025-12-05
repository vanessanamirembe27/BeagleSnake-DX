#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H
#include <QWidget>
#include <Qlabel>
#include <QPushButton>
#include <QVBox Layout>
#include <QHBox Layout>
#include <QStackWidget>

class GameView;
class SnakeGame;
class ToneBuzzer;
class GameWindow : public QWidget
{
  Q_OBJECT
public:
    explicit GameWindow(QWidget *parent = nullptr);

private slots:
    //Menu Navigation
    void startGame();
    void showInstructions();
    void exitGame();
    //In game UI
    void updateScore(int newScore);
    void handleGameOver();
    void pauseGame();
    void restartGame();

private:
    void createMenuScreen();
    void createInstructionsScreen();
    void createGameScreen();
    void connectSignals();

   //Screens
    QStackedWidget *m_stack;
    QWidget *m_menuScreen;
    QWidget *m_instructionScreen;
    QWidget *m_gameScreen;

   // Game components
    GameView *m_view;
    SnakeGame *m_game;
    ToneBuzzer *m_buzzer;

   // In-game UI elements
    Qlabel *m_scorelabel;
    QPushButton *m_pauseButton;
    QPushButton *m_restartButton;

   // Layouts
    QVBoxLayout *m_mainLayout;
    QHBoxLayout *m_topBarLayout;

   //Game State
    bool m_isPaused = false;
};
#endif // GAMEWINDOW_H

