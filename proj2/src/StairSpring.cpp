#include "StairSpring.h"

StairSpring::StairSpring(int pos_y, QWidget *parent) : Stair(pos_y, 50, parent)
{
	LoadImage();
}

StairSpring::~StairSpring()
{
}

void StairSpring::LoadImage()
{
	ImageList.push_back(QPixmap(":/stairs/spring/1"));
	ImageList.push_back(QPixmap(":/stairs/spring/2"));
	ImageList.push_back(QPixmap(":/stairs/spring/3"));
	ImageList.push_back(QPixmap(":/stairs/spring/4"));
	ImageList.push_back(QPixmap(":/stairs/spring/3"));
	ImageList.push_back(QPixmap(":/stairs/spring/2"));

	for (int i = 0; i < ImageList.size(); i++)
		ImageList[i].setMask(ImageList[i].createMaskFromColor(QColor(0, 0, 255), Qt::MaskInColor));
}

double StairSpring::GetHumanStep(int nHumanDirection)
{
	UNUSED_VARIABLE(nHumanDirection);

	return 1;
}

double StairSpring::GetHumanOffset()
{
	return 0;
}

void StairSpring::SetAnimation(int type)
{
	if (nAnimationType != ANIMATION_NONE)
		return;

	nAnimationType = type;
	nLifeChangeValue = 10;
}

void StairSpring::Update()
{
	y--;

	move(x, y - ImageList[nImageId].height() + STAIR_STAND_HEIGHT);
	resize(ImageList[nImageId].width(), ImageList[nImageId].height());

	update();
}
