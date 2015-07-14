#ifndef STAIRNORMAL_H
#define STAIRNORMAL_H

#include "Stair.h"

class StairNormal : public Stair {
public:
	StairNormal(int pos_y, QWidget *parent = 0);
	virtual ~StairNormal();

	virtual double GetHumanStep(int nHumanDirection);
	virtual double GetHumanOffset();
	virtual void Update();

protected:
	virtual void LoadImage();
};

#endif // STAIRNORMAL_H
