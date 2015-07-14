#ifndef STAIRLEFT_H
#define STAIRLEFT_H

#include "Stair.h"

class StairLeft : public Stair {
public:
	StairLeft(int pos_y, QWidget *parent = 0);
	virtual ~StairLeft();

	virtual double GetHumanStep(int nHumanDirection);
	virtual double GetHumanOffset();
	virtual void Update();

protected:
	virtual void LoadImage();
};

#endif // STAIRLEFT_H
