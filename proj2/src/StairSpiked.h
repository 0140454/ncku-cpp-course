#ifndef STAIRSPIKED_H
#define STAIRSPIKED_H

#include "Stair.h"

class StairSpiked : public Stair {
public:
	StairSpiked(int pos_y, QWidget *parent = 0);
	virtual ~StairSpiked();

	virtual double GetHumanStep(int nHumanDirection);
	virtual double GetHumanOffset();
	virtual void Update();

protected:
	virtual void LoadImage();
};

#endif // STAIRSPIKED_H
