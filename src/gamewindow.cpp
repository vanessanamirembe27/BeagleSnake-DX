#include "gamewindow.h"
#include "gameview.h"
#include "snakegame.h"
#include "config.h"

#include <QStackedWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QTimer>
#include <QApplication>

GameWindow::GameWindow(QWidget *parent)
    : QWidget(parent)
{
    // Create the core game components first
    m_game = new SnakeGame(Config::GRID_COLS, Config::GRID_ROWS, this);
    m_view = new GameView(m_game, this);
    m_timer = new QTimer(this);

    // Create the main stack that will hold all our screens
    m_stack = new QStackedWidget(this);

    // Build each screen
    createMenuScreen();
    createGameScreen();
    createGameOverScreen();

    // Add screens to the stack
    m_stack->addWidget(m_menuScreen);
    m_stack->addWidget(m_gameScreen);
    m_stack->addWidget(m_gameOverScreen);

    // Set the main layout for the window
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(m_stack);
    setLayout(mainLayout);

    // Connect all signals
    connectSignals();

    // Start on the menu screen
    showMenu();

    // Set window properties
    setWindowTitle("BeagleSnake");
    setFixedSize(Config::SCREEN_WIDTH_PX, Config::SCREEN_HEIGHT_PX);
}

GameWindow::~GameWindow() {}

void GameWindow::createMenuScreen()
{
    m_menuScreen = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout(m_menuScreen);
    layout->setSpacing(20);
    layout->addStretch();

    QLabel *title = new QLabel("BeagleSnake", m_menuScreen);
    title->setAlignment(Qt::AlignCenter);
    title->setFont(QFont("Sans", 36, QFont::Bold));

    QPushButton *startButton = new QPushButton("Start Game", m_menuScreen);
    connect(startButton, &QPushButton::clicked, this, &GameWindow::startGame);

    m_highScoreLabel_menu = new QLabel("High Score: 0", m_menuScreen);
    m_highScoreLabel_menu->setAlignment(Qt::AlignCenter);

    layout->addWidget(title);
    layout->addWidget(startButton);
    layout->addWidget(m_highScoreLabel_menu);
    layout->addStretch();
}

void GameWindow::createGameScreen()
{
    m_gameScreen = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout(m_gameScreen);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);

    // 1. Create the score label.
    m_scoreLabel_game = new QLabel("Score: 0", m_gameScreen);
    m_scoreLabel_game->setAlignment(Qt::AlignCenter); // Center the text
    // Set a fixed height equal to the top border size from config.h
    m_scoreLabel_game->setFixedHeight(Config::Y_OFFSET);

    // 2. Add the score label to the layout.
    layout->addWidget(m_scoreLabel_game);

    // 3. Add the game view to the layout. It will be placed below the score label.
    layout->addWidget(m_view);

    // 4. Crucial Step: Adjust the game view's margin to pull it up.
    // This makes the game view overlap the space taken by the score label,
    // effectively placing the score label inside the game view's top border.
    // The top margin is negative the height of the score label.
    m_view->setContentsMargins(0, -Config::Y_OFFSET, 0, 0);
}

void GameWindow::createGameOverScreen()
{
    m_gameOverScreen = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout(m_gameOverScreen);
    layout->setSpacing(15);
    layout->addStretch();

    // Store the title label in our new member variable
    m_gameOverTitle_gameOver = new QLabel("Game Over", m_gameOverScreen);
    m_gameOverTitle_gameOver->setAlignment(Qt::AlignCenter);
    m_gameOverTitle_gameOver->setFont(QFont("Sans", 30, QFont::Bold));

    m_finalScoreLabel_gameOver = new QLabel("Your Score: 0", m_gameOverScreen);
    m_finalScoreLabel_gameOver->setAlignment(Qt::AlignCenter);

    m_highScoreLabel_gameOver = new QLabel("High Score: 0", m_gameOverScreen);
    m_highScoreLabel_gameOver->setAlignment(Qt::AlignCenter);

    QPushButton *restartButton = new QPushButton("Restart Game", m_gameOverScreen);
    connect(restartButton, &QPushButton::clicked, this, &GameWindow::restartGame);

    QPushButton *menuButton = new QPushButton("Main Menu", m_gameOverScreen);
    connect(menuButton, &QPushButton::clicked, this, &GameWindow::showMenu);

    layout->addWidget(m_gameOverTitle_gameOver); // Add the member variable to the layout
    layout->addWidget(m_finalScoreLabel_gameOver);
    layout->addWidget(m_highScoreLabel_gameOver);
    layout->addWidget(restartButton);
    layout->addWidget(menuButton);
    layout->addStretch();
}

void GameWindow::connectSignals()
{
    connect(m_timer, &QTimer::timeout, m_game, &SnakeGame::tick);
    connect(m_game, &SnakeGame::gameOver, this, &GameWindow::handleGameOver);
    connect(m_game, &SnakeGame::gameWon, this, &GameWindow::handleGameWon); 
    connect(m_game, &SnakeGame::scoreChanged, this, &GameWindow::updateScore);
}

// --- SLOTS ---

void GameWindow::startGame()
{
    // Switch to the game screen and start a new game
    m_stack->setCurrentWidget(m_gameScreen);
    restartGame();
}

void GameWindow::showMenu()
{
    // Update the high score label on the menu before showing it
    m_highScoreLabel_menu->setText(QString("High Score: %1").arg(m_highScore));
    m_stack->setCurrentWidget(m_menuScreen);
}

void GameWindow::handleGameOver()
{
    m_timer->stop();

    // Set the title text specifically for a loss
    m_gameOverTitle_gameOver->setText("Game Over");

    // Check for and update the high score
    int finalScore = m_game->getScore();
    if (finalScore > m_highScore) {
        m_highScore = finalScore;
    }

    // Update the labels on the game over screen
    m_finalScoreLabel_gameOver->setText(QString("Your Score: %1").arg(finalScore));
    m_highScoreLabel_gameOver->setText(QString("High Score: %1").arg(m_highScore));

    // Switch to the game over screen
    m_stack->setCurrentWidget(m_gameOverScreen);
}

void GameWindow::handleGameWon()
{
    m_timer->stop();

    // Set the title text for a win
    m_gameOverTitle_gameOver->setText("Game Won!");

    // Check for and update the high score
    int finalScore = m_game->getScore();
    if (finalScore > m_highScore) {
        m_highScore = finalScore;
    }

    // Update the labels on the game over screen
    m_finalScoreLabel_gameOver->setText(QString("Your Score: %1").arg(finalScore));
    m_highScoreLabel_gameOver->setText(QString("High Score: %1").arg(m_highScore));

    // Switch to the game over screen
    m_stack->setCurrentWidget(m_gameOverScreen);
}

void GameWindow::restartGame()
{
    // Reset the game logic and score display
    updateScore(0);
    m_game->initGame();

    // Ensure we are on the game screen and start the timer
    m_stack->setCurrentWidget(m_gameScreen);
    m_timer->start(Config::GAME_TICK_SPEED_MS);
}

void GameWindow::updateScore(int score)
{
    // This updates the score label on the main game screen
    m_scoreLabel_game->setText(QString("Score: %1").arg(score));
}