#include "StairLeft.h"

StairLeft::StairLeft(int pos_y, QWidget *parent) : Stair(pos_y, 100, parent)
{
	LoadImage();
	SetAnimation(ANIMATION_INF);
}

StairLeft::~StairLeft()
{
}

void StairLeft::LoadImage()
{
	ImageList.push_back(QPixmap(":/stairs/left/1"));
	ImageList.push_back(QPixmap(":/stairs/left/2"));
	ImageList.push_back(QPixmap(":/stairs/left/3"));
	ImageList.push_back(QPixmap(":/stairs/left/4"));

	for (int i = 0; i < ImageList.size(); i++)
		ImageList[i].setMask(ImageList[i].createMaskFromColor(QColor(0, 0, 255), Qt::MaskInColor));
}

void StairLeft::Update()
{
	y--;

	move(x, y);
	resize(ImageList[nImageId].width(), ImageList[nImageId].height());

	update();
}

double StairLeft::GetHumanStep(int nHumanDirection)
{
	return (nHumanDirection == HUMAN_LEFT) ? 1.5 : 0.4;
}

double StairLeft::GetHumanOffset()
{
	return -1;
}
