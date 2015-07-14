#include "StairOnetime.h"

StairOnetime::StairOnetime(int pos_y, QWidget *parent) : Stair(pos_y, 100, parent)
{
	bTriggered = false;

	LoadImage();
}

StairOnetime::~StairOnetime()
{
}

void StairOnetime::LoadImage()
{
	ImageList.push_back(QPixmap(":/stairs/onetime/1"));
	ImageList.push_back(QPixmap(":/stairs/onetime/2"));
	ImageList.push_back(QPixmap(":/stairs/onetime/3"));
	ImageList.push_back(QPixmap(":/stairs/onetime/4"));
	ImageList.push_back(QPixmap(":/stairs/onetime/5"));
	ImageList.push_back(QPixmap(":/stairs/onetime/6"));
}

double StairOnetime::GetHumanStep(int nHumanDirection)
{
	UNUSED_VARIABLE(nHumanDirection);

	return 1;
}

double StairOnetime::GetHumanOffset()
{
	return 0;
}

bool StairOnetime::IsTriggered()
{
	if (!bTriggered)
	{
		bTriggered = true;
		return false;
	}
	else
		return true;
}

void StairOnetime::Update()
{
	y--;

	move(x, y - (ImageList[nImageId].height() - ImageList[0].height()) / 2);
	resize(ImageList[nImageId].width(), ImageList[nImageId].height());
}
