#ifndef PAUSED_H
#define PAUSED_H
#include <QtWidgets>
#include "Common.h"

class Paused : public QWidget {
public:
	Paused(QWidget *parent = 0);
	virtual ~Paused();

protected:
	virtual void paintEvent(QPaintEvent *event);
};
#endif // PAUSED_H
