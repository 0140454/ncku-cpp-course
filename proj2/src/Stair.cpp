#include "Stair.h"

Stair::Stair(int pos_y, int interval, QWidget *parent) : QWidget(parent)
{
	y = pos_y;
	x = SIDE_WIDTH + rand() % (parent->width() - INFO_WIDTH - SIDE_WIDTH * 2 - STAIR_STAND_WIDTH);

	nIntervalTime = interval;
	nImageId = 0;
	nLifeChangeValue = 10;
	nAnimationType = ANIMATION_NONE;

	move(x, y);
	startTimer(nIntervalTime);
}

Stair::~Stair()
{
	ImageList.clear();
}

QPoint Stair::GetRealTimePos()
{
	return QPoint(x, y);
}

void Stair::SetAnimation(int type)
{
	nAnimationType = type;
}

void Stair::timerEvent(QTimerEvent *event)
{
	UNUSED_VARIABLE(event);

	if (nAnimationType == ANIMATION_NONE)
		return;

	if ((++nImageId) == ImageList.size())
	{
		if (nAnimationType == ANIMATION_ONETIME)
			nAnimationType = ANIMATION_NONE;
		nImageId = 0;
	}
}

void Stair::paintEvent(QPaintEvent *event)
{
	UNUSED_VARIABLE(event);

	QPainter painter(this);

	if (!ImageList.empty())
		painter.drawPixmap(0, 0, ImageList[nImageId]);
}

int Stair::GetLifeChangeValue()
{
	int ret = nLifeChangeValue;

	nLifeChangeValue = 0;

	return ret;
}
