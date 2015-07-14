#include "StairNormal.h"

StairNormal::StairNormal(int pos_y, QWidget *parent) : Stair(pos_y, 100, parent)
{
	LoadImage();
}

StairNormal::~StairNormal()
{
}

void StairNormal::LoadImage()
{
	ImageList.push_back(QPixmap(":/stairs/normal"));
}

double StairNormal::GetHumanStep(int nHumanDirection)
{
	UNUSED_VARIABLE(nHumanDirection);

	return 1;
}

double StairNormal::GetHumanOffset()
{
	return 0;
}

void StairNormal::Update()
{
	y--;

	move(x, y);
	resize(ImageList[nImageId].width(), ImageList[nImageId].height());
}
