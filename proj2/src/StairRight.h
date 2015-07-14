#ifndef STAIRRIGHT_H
#define STAIRRIGHT_H

#include "Stair.h"

class StairRight : public Stair {
public:
	StairRight(int pos_y, QWidget *parent = 0);
	virtual ~StairRight();

	virtual double GetHumanStep(int nHumanDirection);
	virtual double GetHumanOffset();
	virtual void Update();

protected:
	virtual void LoadImage();
};

#endif // STAIRRIGHT_H
