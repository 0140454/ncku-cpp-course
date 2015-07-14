#ifndef SPIKED_H
#define SPIKED_H
#include <QtWidgets>
#include "Stair.h"
#include "Common.h"

class Spiked : public QWidget {
public:
	Spiked(QWidget *parent = 0);
	virtual ~Spiked();

protected:
	virtual void paintEvent(QPaintEvent *event);
};

#endif // SPIKED_H
