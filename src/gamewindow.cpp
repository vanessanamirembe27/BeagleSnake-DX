#include "gamewindow.h"
#include "gameview.h"
#include "snakegame.h"
#include "config.h"
#include <QFont>
#include <QMessageBox>

GameWinddow::GameWindow(QWidget *parent)
    : QWidget(parent)
{
    // Create game screen including game logic
    m_view = new GameView(this);
    m_game = m_view->findChild<SnakeGame*>(); //game object is inside gameview

    createUI();
    connectSignals();
    setStyleSheet("background-color: black;");  //Dark Theme
    showFullScreen();
} 
void GameWindow::createUI()
{
  // Score label
  m_scoreLabel = new Qlabel("Score: 0");
  m_scoreLabel->setFont(QFont("Dejavu Sans", 24, QFont::Bold));
  m_scoreLabel->setStyleSheet("color: white;");

  // Pause Button
  m_pauseButton = new QPushButton("Pause");
  m_pauseButton->setFont(QFont("Dejavu Sans", 18));
  m_pauseButton->setStyleSheet(
       "QPushButton { background-color: #444; color: white; padding: 8px; border-radius: 8px; }"
       "QPushButton:pressed { background-color: #666; color: grey; }"
    );

   // Restart Button
   m_restartButton = new QPushButton("Restart");
   m_restartButton->setFont(QFont("Dejavu Sans", 18));
   m_restartButton->setStyleSheet(
     "QPushButton { background-color: #006600; color: white; padding: 8px; border-radius: 8px; }"
       "QPushButton:pressed { background-color: #009900; color: green; }"
    );

   // Top Bar Layout
   m_topBarLayout = new QHBoxLayout();
   m_topBarLayout->addWidget(m_scoreLabel);
   m_topBarLayout->addStretch();
   m_topBarLayout->addWidget(m_pauseButton);
   m_topBarLayout->addWidget(m_restartButton);

  // Main Layout
  m_mainLayout = new QVBoxLayout(this);
  m_mainLayout->addLayout(m_topBarLayout);
  m_mainLayout->addWidget(m_view);
  setLayout(m_mainLayout);
}

void GameWindow::conectSignals()
{
  connect(m_game, &SnakeGame::scoreChanged,
          this, &GameWindow::updateScore);
  connect(m_game, &SnakeGame::gameOver,
          this, &GameWindow::handleGameOver);
  connect(m_pauseButton, &QPushButton::clicked,
          this, &GameWindow::pauseGame);
  connect(m_restartButton, &QPushButton::clicked,
          this, &GameWindow::restartGame);
}

void GameWindow::updateScore(int newScore)
{
  m_scoreLabel->setText(QString("Score: %1").arg(newScore));
}

void GameWindow::pauseGame()
{
  m_game->togglePause();

  if (!m_isPaused) {
      m_pauseButton->setText("Resume);
      m_isPaused = true;
        } else {
          m_pauseButton->setText("Pause");
          m_isPaused = false;
  }
}

void GameWindow::restartGame()
{
  m_game->initGame();
  m_pauseButton->setText('Pause");
  m_isPaused = false;
  m_scoreLabel->setText("Score: 0");
}

void GameWindow:handleGameOver()
{
  QMessageBox::information(
       this,
       "Game Over",
       QString("Your final score: %1\nPress Restart to try again.")
          .arg(m_game->getScore())
    );
    m_pauseButton->setText("Pause");
    m_isPaused = false;
}
    
