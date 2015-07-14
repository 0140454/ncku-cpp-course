#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
	pGame = NULL;
	pPaused = NULL;

	initMenuBar();

	setWindowTitle("小朋友下樓梯");
	setFixedSize(WINDOW_WIDTH, WINDOW_HEIGHT);

	NewGame();
	pGame->SetGameOver();
}

MainWindow::~MainWindow()
{
	if (pGame) delete pGame;

	delete pNewGame;
	delete pPauseGame;
	delete pStopGame;
	delete pExit;
	delete pHelp;
	delete pAbout;
}

void MainWindow::initMenuBar()
{
	/// Initialize QAction
	pNewGame = new QAction("新遊戲(&N)", this);
	pPauseGame = new QAction("暫停遊戲(&P)", this);
	pStopGame = new QAction("停止遊戲(&Q)", this);
	pExit = new QAction("結束本程式(&X)", this);

	pHelp = new QAction("檢視說明(&V)", this);
	pAbout = new QAction("關於(&A)", this);
	/// Set Shortcut
	pNewGame->setShortcut(QKeySequence("CTRL+N"));
	pPauseGame->setShortcut(QKeySequence("CTRL+P"));
	pStopGame->setShortcut(QKeySequence("CTRL+Q"));
	pExit->setShortcut(QKeySequence("CTRL+X"));

	pHelp->setShortcut(QKeySequence("F1"));
	pAbout->setShortcut(QKeySequence("CTRL+A"));
	/// Connect slots to QAction
	connect(pNewGame, SIGNAL(triggered()), this, SLOT(NewGame()));
	connect(pPauseGame, SIGNAL(triggered()), this, SLOT(PauseGame()));
	connect(pStopGame, SIGNAL(triggered()), this, SLOT(StopGame()));
	connect(pExit, SIGNAL(triggered()), this, SLOT(Exit()));

	connect(pHelp, SIGNAL(triggered()), this, SLOT(Help()));
	connect(pAbout, SIGNAL(triggered()), this, SLOT(About()));
	/// Add to Menu Bar
	pGameMenu = this->menuBar()->addMenu("遊戲(&G)");
	pGameMenu->addAction(pNewGame);
	pGameMenu->addAction(pPauseGame);
	pGameMenu->addAction(pStopGame);
	pGameMenu->addSeparator();
	pGameMenu->addAction(pExit);

	pHelpMenu = this->menuBar()->addMenu("說明(&H)");
	pHelpMenu->addAction(pHelp);
	pHelpMenu->addSeparator();
	pHelpMenu->addAction(pAbout);
	/// Check Status
	pPauseGame->setEnabled(false);
	pStopGame->setEnabled(false);
}

void MainWindow::ResetMenu()
{
	pPauseGame->setText("暫停遊戲(&P)");
	pPauseGame->setEnabled(false);

	pStopGame->setEnabled(false);
}

void MainWindow::NewGame()
{
	if (pGame) delete pGame;
	pGame = new ShaftGame(this);
	setCentralWidget(pGame);

	pPauseGame->setEnabled(true);
	pStopGame->setEnabled(true);
}

void MainWindow::PauseGame()
{
	if (pGame)
	{
		if (!pGame->IsPaused())
		{
			pPauseGame->setText("繼續遊戲(&P)");
			pPaused = new Paused(this);
			pPaused->show();
		}
		else
		{
			pPauseGame->setText("暫停遊戲(&P)");
			delete pPaused;
			pPaused = NULL;
		}

		pGame->SetPaused(!pGame->IsPaused());
	}
}

void MainWindow::StopGame()
{
	if (pGame)
	{
		pGame->SetPaused(false);
		pGame->SetGameOver();
	}
}

void MainWindow::Exit()
{
	exit(0);
}

void MainWindow::Help()
{
	QMessageBox::information(this, "說明", "這個程式的組成是這樣的...\n\n總共 1568 行\n\n"
							 "79 % Code\n"
							 "02 % Comments\n"
							 "20 % Empty\n");
}

void MainWindow::About()
{
	QMessageBox::about(this, "關於",
					   "C++程式設計 - Project 2 (小朋友下樓梯)\n\n"
					   "作者: F74022167 (吳勃興)");
}
