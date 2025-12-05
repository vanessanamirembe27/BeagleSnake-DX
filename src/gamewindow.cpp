#include "gamewindow.h"
#include "gameview.h"
#include "snakegame.h"
#include "tonebuzzer.h"
#include "config.h"
#include <QFont>
#include <QMessageBox>
#include <QPixmap>
#include <QBrush>

GameWindow::GameWindow(QWidget *parent)
    : QWidget(parent)
{
    // Create buzzer for Mario sounds
    m_buzzer = new Tonebuzzer("/sys/class/pwm/pwmchip1/pwm0", this);

    //Screen Stack(menu, instructions, game)
    m_stack = new QStackedWidget(this);
    createMenuScreen();
    createInstructionScreen();
    createGameScreen();
    //Start on the menu page
    m_stack->setCurrentIndez(0);

    // Wrap Stack in a layout
    m_mainLayout = new QVBoxLayout(this);
    m_mainLayout->addWidget(m_stack);
    setLayout(m_mainLayout);
    showFullscreen();
}
    //Menu Screen with Green background
void GameWindow::createMenuScreen()
{
    m_menuScreen = new QWidget(this);
    QVBoxLayout *menuLayout = new QVBoxLayout(m_menuScreen);

    //Grass Background
    m_menuScreen->setAutoFillBackground(true);
    QPalette pal = m_menuScreen->palette();
    pal.setBrush(QPalette::Window,
                 QBrush(QPixmap(":/assets/grass.png").scaled(800,480,
                 Qt::IgnoreAspectRatio, Qt::SmoothTransformation)));
    m_menuScreen->setPalette(pal);

    Qlabel*title = new Qlabel("BeagleSnake DX");
    title->setAlignment(Qt::AlignCenter);
    title->setFont(QFont("Dejavu Sans", 36, QFont::Bold));
    title->setStyleSheet("color: whitr; text-shadow: 2px 2px black;");

    //Start Button
    QPushButton *startBtn = new QPushButton("Start Game");
    startBtn->setFixedHeight(60);
    startBtn->setStyleSheet(
        "QPushButton { ont-size: 28px; padding: 10px; background-color: rgba(0,0,0,0.5);"
        "color: white; border-radius: 12px; }"
        "QPushButton:pressed { background-color: rgba(0,0,0,0.8); }");
    connect(startBtn, &QPushButton::clicked, this, &GameWindow::startGame);

    // Exit Button
    QPushButton *exitBtn = new QPushButton("Exit");
    exitBtn->setFixedHeight(50);
    exitBtn->setStyleSheet(
        "QPushButton { font-size: 22px; padding: 10px; background-color: rgba(0,0,0,0.5);"
        "color: white; border-radius: 12px; }"
        "QPushButton:pressed { background-color: rgba(0,0,0,0.8); }");
    connect(exitBtn, &QPushButton::clicked, this, &GameWindow::exitGame);

    // Layout Placement
    menuLayout->addStretch();
    menuLayout->addWidget(title);
    menuLayout->addSpacing(40);
    menuLayout->addWidget(startBtn, 0, Qt::AlignCenter);
    menuLayout->addWidget(howBtn, 0, Qt::AlignCenter);
    menuLayout->addWidget(exitBtn, 0, Qt::AlignCenter);
    menuLayout->addStretch();

    m_stack->addWidget(m_menuScreen);
}

// Instruction Screen
void GameWindow::createInstructionScreen()
{
    m_instructionScreen = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(m_instructionScreen);

    // Background
    m_instructionScreen->setAutoFillBackground(true);
    QPalette pal = m_instructionScreen->palette();
    pal.setBrush(QPalette::Window,
                 QBrush(QPixmap(":/assets/grass.png").scaled(800, 480,
                 Qt::IgnoreAspectRatio, Qt::SmoothTransformation)));
    m_instructionScreen->setPalette(pal);

    QLabel *info = new QLabel(
        "Controls:\n"
        "- Swipe or tap to move\n"
        "- Arrow keys for keyboard\n"
        "- Eat food to grow\n"
        "- Avoid walls & yourself"
    );
    info->setAlignment(Qt::AlignCenter);
    info->setStyleSheet("color: white; font-size: 24px; text-shadow: 2px 2px black;");

    QPushButton *backBtn = new QPushButton("Back");
    backBtn->setStyleSheet(
        "QPushButton { font-size: 22px; padding: 8px; background-color: rgba(0,0,0,0.6);"
        "color: white; border-radius: 10px; }"
        "QPushButton:pressed { background-color: rgba(0,0,0,0.9); }");
    backBtn->setFixedHeight(50);

    connect(backBtn, &QPushButton::clicked, [this]() {
        m_stack->setCurrentIndex(0);
    });

    layout->addStretch();
    layout->addWidget(info);
    layout->addSpacing(30);
    layout->addWidget(backBtn, 0, Qt::AlignCenter);
    layout->addStretch();

    m_stack->addWidget(m_instructionScreen);
}
  

    // Create game screen including game logic
    m_view = new GameView(this);
    m_game = m_view->findChild<SnakeGame*>(); //game object is inside gameview

    createUI();
    connectSignals();
    setStyleSheet("background-color: black;");  //Dark Theme
    showFullScreen();
} 
void GameWindow::createGameScreen()
{
    m_gameScreen = new QWidget(this);
    QVBoxLayout = new QVBoxLayout(m_gameScreen);
    m_view = new GameView(this);
    m_game = m_view->findChild<SnakeGame*();
    
  // Score label
  m_scoreLabel = new Qlabel("Score: 0");
  m_scoreLabel->setFont(QFont("Dejavu Sans", 22, QFont::Bold));
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

   connectSignals();
    layout->addLayout(m_topBarLayout);
    layout->addWidget(m_view);
    m_gameScreen->setLayout(layout);
    m_stack-> addWidget(m_gameScreen);
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

// Start Game
void GameWindow::startGame()
{
  if (m_buzzer)
      m_buzzer->playMarioStart();
m_stack->setCurrentIndex(2); //switch to game screen

//Instructions
void GameWindow::showInstructions()
{
  m_stack->setCurrentIndex(1);
}
void GameWindow::exitGame()
{
  QApplication::quit();
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
    

