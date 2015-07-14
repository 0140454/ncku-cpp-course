#include "StairRight.h"

StairRight::StairRight(int pos_y, QWidget *parent) : Stair(pos_y, 100, parent)
{
	LoadImage();
	SetAnimation(ANIMATION_INF);
}

StairRight::~StairRight()
{
}

void StairRight::LoadImage()
{
	ImageList.push_back(QPixmap(":/stairs/right/1"));
	ImageList.push_back(QPixmap(":/stairs/right/2"));
	ImageList.push_back(QPixmap(":/stairs/right/3"));
	ImageList.push_back(QPixmap(":/stairs/right/4"));

	for (int i = 0; i < ImageList.size(); i++)
		ImageList[i].setMask(ImageList[i].createMaskFromColor(QColor(0, 0, 255), Qt::MaskInColor));
}

double StairRight::GetHumanStep(int nHumanDirection)
{
	return (nHumanDirection == HUMAN_LEFT) ? 0.4 : 1.5;
}

double StairRight::GetHumanOffset()
{
	return 1;
}

void StairRight::Update()
{
	y--;

	move(x, y);
	resize(ImageList[nImageId].width(), ImageList[nImageId].height());
}
