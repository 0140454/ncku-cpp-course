#include "Paused.h"

Paused::Paused(QWidget *parent) : QWidget(parent)
{
	resize(PAUSED_WIDTH, PAUSED_HEIGHT);
	move((WINDOW_WIDTH - PAUSED_WIDTH) / 2, (WINDOW_HEIGHT - PAUSED_HEIGHT) / 2);
}

Paused::~Paused()
{
}

void Paused::paintEvent(QPaintEvent *event)
{
	UNUSED_VARIABLE(event);

	QPainter painter(this);

	painter.drawPixmap(0, 0, QPixmap(":/images/pause"));
}
