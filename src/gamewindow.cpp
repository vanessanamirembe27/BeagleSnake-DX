#include "gamewindow.h"
#include "gameview.h"
#include "snakegame.h"
#include "config.h"
#include <QTimer>
#include <QVBoxLayout>

GameWindow::GameWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // 1. Create the core game components
    m_game = new SnakeGame(Config::GRID_COLS, Config::GRID_ROWS, this);
    m_view = new GameView(m_game, this); // Pass the game instance to the view
    m_timer = new QTimer(this);

    // 2. Set the GameView as the central widget
    setCentralWidget(m_view);

    // 3. Create the overlay widgets (initially hidden)
    createGameOverWidgets();

    // 4. Connect all signals and slots
    connect(m_timer, &QTimer::timeout, m_game, &SnakeGame::tick);
    connect(m_game, &SnakeGame::gameOver, this, &GameWindow::handleGameOver);
    connect(m_game, &SnakeGame::scoreChanged, this, &GameWindow::updateScore);
    connect(m_restartButton, &QPushButton::clicked, this, &GameWindow::restartGame);

    // Start the game
    m_timer->start(Config::GAME_TICK_SPEED_MS);
}

GameWindow::~GameWindow()
{
}

void GameWindow::createGameOverWidgets()
{
    m_gameOverWidget = new QWidget(this);
    m_scoreLabel = new QLabel(this);
    m_restartButton = new QPushButton("Restart", this);

    // Style the widgets
    m_scoreLabel->setAlignment(Qt::AlignCenter);
    QFont scoreFont = m_scoreLabel->font();
    scoreFont.setPointSize(24);
    m_scoreLabel->setFont(scoreFont);
    
    QPalette scorePalette;
    scorePalette.setColor(QPalette::WindowText, Config::COLOR_GAMEOVER_TEXT);
    m_scoreLabel->setPalette(scorePalette);
    
    m_restartButton->setFont(scoreFont);

    // Create a layout for the overlay
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addStretch();
    layout->addWidget(m_scoreLabel);
    layout->addWidget(m_restartButton);
    layout->addStretch();
    m_gameOverWidget->setLayout(layout);

    // Style the overlay background using the config constant
    QPalette palette;
    palette.setColor(QPalette::Window, Config::COLOR_GAMEOVER_OVERLAY);
    m_gameOverWidget->setPalette(palette);
    m_gameOverWidget->setAutoFillBackground(true);

    m_gameOverWidget->hide(); // Hide it until the game is over
}

void GameWindow::handleGameOver()
{
    m_timer->stop();
    m_gameOverWidget->setGeometry(this->rect()); // Make it fill the window
    m_gameOverWidget->show();
}

void GameWindow::restartGame()
{
    m_gameOverWidget->hide();
    m_game->initGame();
    m_timer->start(Config::GAME_TICK_SPEED_MS);
}

void GameWindow::updateScore(int score)
{
    m_scoreLabel->setText(QString("Game Over!\nScore: %1").arg(score));
}