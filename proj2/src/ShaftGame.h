#ifndef SHAFTGAME_H
#define SHAFTGAME_H

#include <QtWidgets>
#include "Stairs.h"
#include "Human.h"
#include "Spiked.h"
#include "ScorePanel.h"
#include "MessagePanel.h"

class ShaftGame : public QWidget {
public:
	ShaftGame(QWidget *parent = 0);
	virtual ~ShaftGame();

	bool IsPaused();
	bool IsGameOver();
	void SetGameOver();
	void SetPaused(bool bEnabled);
	int GetHumanLife();

protected:
	virtual void paintEvent(QPaintEvent* event);
	virtual void keyPressEvent(QKeyEvent *event);
	virtual void keyReleaseEvent(QKeyEvent *event);
	virtual void timerEvent(QTimerEvent *event);

private:
	void InitStairs();

private:
	int nBackgroundOffset, nBackgroundTimerId, nHumanTimerId;
	int nHumanLife, nLastTime, nElapsedTime, nBackgroudInterval;

	int nLastPressKey;

	bool bPaused;
	bool bGameOver;

	Human *pHuman;
	Spiked *pSpiked;
	ScorePanel *pScorePanel;
	MessagePanel *pMessagePanel;
	QList<Stair*> stairs;

	QSettings *setting;
};

#endif // SHAFTGAME_H
