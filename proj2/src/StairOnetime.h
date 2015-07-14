#ifndef STAIRONETIME_H
#define STAIRONETIME_H

#include "Stair.h"

class StairOnetime : public Stair {
public:
	StairOnetime(int pos_y, QWidget *parent = 0);
	virtual ~StairOnetime();

	virtual double GetHumanStep(int nHumanDirection);
	virtual double GetHumanOffset();
	virtual void Update();

	bool IsTriggered();

protected:
	bool bTriggered;

	virtual void LoadImage();
};

#endif // STAIRONETIME_H
