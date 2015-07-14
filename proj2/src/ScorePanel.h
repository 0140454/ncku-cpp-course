#ifndef SCOREPANEL_H
#define SCOREPANEL_H
#include <QtWidgets>
#include "Common.h"

class ScorePanel : public QWidget{
public:
	ScorePanel(QWidget *parent = 0);
	virtual ~ScorePanel();

	void operator++(int);
	int GetFloor();

protected:
	virtual void paintEvent(QPaintEvent *event);

private:
	QPixmap *pBasement;
	QPixmap *pFloor;
	QPixmap *pNumber;

	int nFloor;
	char szFloor[5];
};

#endif // SCOREPANEL_H
