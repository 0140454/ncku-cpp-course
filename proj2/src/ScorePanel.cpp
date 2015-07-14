#include "ScorePanel.h"

ScorePanel::ScorePanel(QWidget *parent) : QWidget(parent)
{
	nFloor = 0;

	pBasement = new QPixmap(":/score/basement");
	pFloor = new QPixmap(":/score/floor");
	pNumber = new QPixmap(":/score/number");

	pBasement->setMask(pBasement->createMaskFromColor(QColor(0, 0, 255), Qt::MaskInColor));
	pFloor->setMask(pFloor->createMaskFromColor(QColor(0, 0, 255), Qt::MaskInColor));
	pNumber->setMask(pNumber->createMaskFromColor(QColor(0, 0, 255), Qt::MaskInColor));

	move(WINDOW_WIDTH - INFO_WIDTH + EDGE_OFFSET, EDGE_OFFSET * 4);
	resize(pBasement->width() + pNumber->width() * 4 + pFloor->width(), pBasement->height());
}

ScorePanel::~ScorePanel()
{
	delete pBasement;
	delete pFloor;
	delete pNumber;
}

void ScorePanel::operator++(int)
{
	nFloor++;
	update();
}

void ScorePanel::paintEvent(QPaintEvent *event)
{
	UNUSED_VARIABLE(event);

	QPainter painter(this);

	painter.drawPixmap(0, 0, *pBasement);
	sprintf(szFloor, "%04d", nFloor);
	for (int i = 0; i < 5; i++)
	{
		szFloor[i] -= '0';
		painter.drawPixmap(pBasement->width() + pNumber->width() * i
							, 0, *pNumber, 0, pNumber->width() * szFloor[i], pNumber->width(), pNumber->width());
	}
	painter.drawPixmap(pBasement->width() + pNumber->width() * 4, 0, *pFloor);
}

int ScorePanel::GetFloor()
{
	return nFloor;
}
