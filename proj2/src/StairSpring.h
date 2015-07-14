#ifndef STAIRSPRING_H
#define STAIRSPRING_H

#include "Stair.h"

class StairSpring : public Stair {
public:
	StairSpring(int pos_y, QWidget *parent = 0);
	virtual ~StairSpring();

	virtual double GetHumanStep(int nHumanDirection);
	virtual double GetHumanOffset();
	virtual void Update();
	virtual void SetAnimation(int type);

protected:
	virtual void LoadImage();
};

#endif // STAIRSPRING_H
