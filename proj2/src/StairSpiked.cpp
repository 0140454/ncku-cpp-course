#include "StairSpiked.h"

StairSpiked::StairSpiked(int pos_y, QWidget *parent) : Stair(pos_y, 100, parent)
{
	LoadImage();

	nLifeChangeValue = -50;
}

StairSpiked::~StairSpiked()
{
}

void StairSpiked::LoadImage()
{
	ImageList.push_back(QPixmap(":/stairs/spiked/down"));
}

double StairSpiked::GetHumanStep(int nHumanDirection)
{
	UNUSED_VARIABLE(nHumanDirection);

	return 1;
}

double StairSpiked::GetHumanOffset()
{
	return 0;
}

void StairSpiked::Update()
{
	y--;

	move(x, y);
	resize(ImageList[nImageId].width(), ImageList[nImageId].height());
}
