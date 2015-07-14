#include "Stairs.h"

Stair *GenStair(int pos_y, QWidget *parent)
{
	Stair *pStair = NULL;

	int type = rand() % STAIR_TYPE_CNT;

	switch(type)
	{
	case STAIR_NORMAL:
		pStair = new StairNormal(pos_y, parent);
		break;
	case STAIR_LEFT:
		pStair = new StairLeft(pos_y, parent);
		break;
	case STAIR_RIGHT:
		pStair = new StairRight(pos_y, parent);
		break;
	case STAIR_SPIKED:
		pStair = new StairSpiked(pos_y, parent);
		break;
	case STAIR_SPRING:
		pStair = new StairSpring(pos_y, parent);
		break;
	case STAIR_ONETIME:
		pStair = new StairOnetime(pos_y, parent);
		break;
	}

	return pStair;
}
