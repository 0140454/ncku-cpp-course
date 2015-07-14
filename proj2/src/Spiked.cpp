#include "Spiked.h"

Spiked::Spiked(QWidget *parent) : QWidget(parent)
{
	resize(WINDOW_WIDTH - INFO_WIDTH - SIDE_WIDTH * 2, STAIR_STAND_HEIGHT);
	move(SIDE_WIDTH, 0);
}

Spiked::~Spiked()
{
}

void Spiked::paintEvent(QPaintEvent *event)
{
	UNUSED_VARIABLE(event);

	QPainter painter(this);

	QPixmap SpikedImage(":/images/spiked");
	SpikedImage.setMask(SpikedImage.createMaskFromColor(QColor(0, 0, 255), Qt::MaskInColor));

	painter.drawTiledPixmap(0, 0, WINDOW_WIDTH - INFO_WIDTH - SIDE_WIDTH * 2, STAIR_STAND_HEIGHT, SpikedImage);
}
