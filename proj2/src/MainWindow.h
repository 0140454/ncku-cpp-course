#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ShaftGame.h"
#include "Paused.h"

class MainWindow : public QMainWindow {
	Q_OBJECT

public:
	MainWindow(QWidget *parent = 0);
	virtual ~MainWindow();

	void ResetMenu();

protected slots:
	void NewGame();
	void PauseGame();
	void StopGame();
	void Exit();

	void Help();
	void About();

private:
	void initMenuBar();

private:
	QMenu *pGameMenu;
	QAction *pNewGame;
	QAction *pPauseGame;
	QAction *pStopGame;
	QAction *pExit;

	QMenu *pHelpMenu;
	QAction *pHelp;
	QAction *pAbout;

	ShaftGame *pGame;
	Paused *pPaused;
};

#endif // MAINWINDOW_H

