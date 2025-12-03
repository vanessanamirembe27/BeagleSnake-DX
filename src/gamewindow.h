#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H
#include <QWidget>
#include <Qlabel>
#include <QPushButton>
#include <QVBox Layout>
#include <QHBox Layout>

class GameView;
class SnakeGame;
class GameWindow : public QWidget
{
  Q_OBJECT
public:
    explicit GameWindow(QWidget *parent = nullptr);

private slots:
    void updateScore(int newScore);
    void handleGameOver();
    void pauseGame();
    void restartGame();

private:
    void createUI();
    void connectSignals();

    GameView *m_view;
    SnakeGame *m_game;
    Qlabel *m_scorelabel;
    QPushButton *m_pauseButton;
    QPushButton *m_restartButton;
    QVBoxLayout *m_mainLayout;
    QHBoxLayout *m_topBarLayout;
    bool m_isPaused = false;
};
#endif //
