#ifndef STAIR_H
#define STAIR_H

#include <QtWidgets>
#include "Common.h"

#define STAIR_NORMAL		0
#define STAIR_LEFT			1
#define STAIR_RIGHT			2
#define STAIR_SPIKED		3
#define STAIR_ONETIME		4
#define STAIR_SPRING		5

#define ANIMATION_NONE		-100
#define ANIMATION_INF		100
#define ANIMATION_ONETIME	200

#define STAIR_TYPE_CNT		6

class Stair : public QWidget {
public:
	Stair(int pos_y, int interval, QWidget *parent = 0);
	virtual ~Stair();

	virtual void Update() = 0;
	virtual void SetAnimation(int type);

	QPoint GetRealTimePos();
	int GetLifeChangeValue();

	virtual double GetHumanStep(int nHumanDirection) = 0; // you SHOULD return a POSITIVE value
	virtual double GetHumanOffset() = 0;

protected:
	virtual void LoadImage() = 0; // you SHOULD call this function in CONSTRUCTOR
	virtual void paintEvent(QPaintEvent *event);
	virtual void timerEvent(QTimerEvent *event);

protected:
	int nImageId;
	int x, y;

	int nLifeChangeValue;
	int nIntervalTime;
	int nAnimationType;

	QList<QPixmap> ImageList;
};

#endif // STAIRS_H
