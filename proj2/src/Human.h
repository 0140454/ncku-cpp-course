#ifndef HUMAN_H
#define HUMAN_H

#include <QtWidgets>
#include "Stairs.h"
#include "Common.h"

class Human : public QWidget{
public:
	Human(int pos_x, int pos_y, QWidget *parent = 0);
	virtual ~Human();

	void SetDirection(int direction = -1);
	int GetStatus();
	int Update(bool bHumanTimer = false);

protected:
	virtual void paintEvent(QPaintEvent *event);
	virtual void timerEvent(QTimerEvent *event);

	Stair *FindStair();

private:
	int nStatus;
	int nImageId, nWarnCount;
	double x, y, speed;
};

#endif // HUMAN_H
