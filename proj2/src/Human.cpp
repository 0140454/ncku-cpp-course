#include "Human.h"
#include "Spiked.h"
#include "ShaftGame.h"
#include <QSound>
#include <ctime>

Human::Human(int pos_x, int pos_y, QWidget *parent) : QWidget(parent)
{
	x = pos_x, y = pos_y;
	nImageId = 0;
	nWarnCount = 0;
	nStatus = HUMAN_DROP;
	speed = 0.5;

	resize(HUMAN_WIDTH, HUMAN_HEIGHT);
	move(x, y);
	startTimer(100);
}

Human::~Human()
{
}

Stair *Human::FindStair()
{
	Stair *pStair = dynamic_cast<Stair*>(parentWidget()->childAt(pos().x() + 6, pos().y() + HUMAN_HEIGHT));
	if (!pStair)
		pStair = dynamic_cast<Stair*>(parentWidget()->childAt(pos().x() + width() - 1 - 6, pos().y() + HUMAN_HEIGHT));

	return pStair;
}

int Human::Update(bool bHumanTimer)
{
	raise();

	if (dynamic_cast<Spiked*>(parentWidget()->childAt(pos().x(), pos().y() - 1)))
	{
		y += STAIR_STAND_HEIGHT;
		move(x, y);

		nStatus = (nStatus & ~HUMAN_STAND) | HUMAN_DROP;
		speed = 0.5;

		nWarnCount = 6;

		return -50;
	}
	else
	{
		Stair *pStair = FindStair();

		if (!pStair)
			nStatus = (nStatus & ~HUMAN_STAND) | HUMAN_DROP, speed += 0.02;
		else
		{
			if (dynamic_cast<StairSpring*>(pStair))
				speed = -1.38, nStatus = (nStatus & ~HUMAN_STAND) | HUMAN_DROP;
			else if (dynamic_cast<StairOnetime*>(pStair))
			{
				nStatus = (nStatus & ~HUMAN_STAND) | HUMAN_DROP;

				if (!dynamic_cast<StairOnetime*>(pStair)->IsTriggered())
				{
					speed = 0;
					QSound::play(":/sounds/warning");
				}
				else
				{
					speed += 0.02;
					if (speed < 0.25) nStatus = (nStatus & ~HUMAN_DROP) | HUMAN_STAND;
				}
			}
			else if (abs(pStair->GetRealTimePos().y() - (y + HUMAN_HEIGHT)) >= 2)
			{
				if (abs(pStair->GetRealTimePos().y() - (y + HUMAN_HEIGHT)) <= 6)
					speed = 0.5, y = pStair->GetRealTimePos().y() - HUMAN_HEIGHT, nStatus = (nStatus & ~HUMAN_DROP) | HUMAN_STAND;
				else
					speed = 0.5, nStatus = (nStatus & ~HUMAN_STAND) | HUMAN_DROP;
			}
			else
				speed = 0.5, nStatus = (nStatus & ~HUMAN_DROP) | HUMAN_STAND;

			if (dynamic_cast<StairSpring*>(pStair))
				dynamic_cast<StairSpring*>(pStair)->SetAnimation(ANIMATION_ONETIME);
			if (dynamic_cast<StairOnetime*>(pStair))
				dynamic_cast<StairOnetime*>(pStair)->SetAnimation(ANIMATION_ONETIME);
		}

		if (nStatus & HUMAN_STAND)
			y -= (bHumanTimer) ? 0 : 1;
		else
			y += speed;

		if (nStatus & HUMAN_LEFT)
			x -= (!pStair) ? 1 : pStair->GetHumanStep(HUMAN_LEFT);
		else if (nStatus & HUMAN_RIGHT)
			x += (!pStair) ? 1 : pStair->GetHumanStep(HUMAN_RIGHT);
		else if (nStatus == HUMAN_STAND)
			x += (!pStair) ? 0 : pStair->GetHumanOffset();

		if (x <= SIDE_WIDTH)
			x = SIDE_WIDTH;
		if (x >= parentWidget()->width() - INFO_WIDTH - SIDE_WIDTH - HUMAN_WIDTH)
			x = parentWidget()->width() - INFO_WIDTH - SIDE_WIDTH - HUMAN_WIDTH;

		move(x, y);

		update();

		int nLifeChangeValue = (!pStair) ? 0 : pStair->GetLifeChangeValue();

		if (nLifeChangeValue < 0)
			nWarnCount = 6;

		if (nLifeChangeValue != 0 && dynamic_cast<ShaftGame*>(parentWidget())->GetHumanLife() > -50)
		{
			if (dynamic_cast<StairNormal*>(pStair))
				QSound::play(":/sounds/normal");
			else if (dynamic_cast<StairSpiked*>(pStair))
				QSound::play(":/sounds/warning");
			else if (dynamic_cast<StairSpring*>(pStair))
				QSound::play(":/sounds/spring");
			else if (dynamic_cast<StairOnetime*>(pStair))
				QSound::play(":/sounds/onetime");
			else if (dynamic_cast<StairLeft*>(pStair) || dynamic_cast<StairRight*>(pStair))
				QSound::play(":/sounds/normal");
		}

		return nLifeChangeValue;
	}
}

void Human::SetDirection(int direction)
{
	nStatus &= ~HUMAN_LEFT;
	nStatus &= ~HUMAN_RIGHT;
	if (direction != -1) nStatus |= direction;
}

int Human::GetStatus()
{
	return nStatus;
}

void Human::timerEvent(QTimerEvent *event)
{
	UNUSED_VARIABLE(event);

	if (dynamic_cast<ShaftGame*>(parentWidget()) && dynamic_cast<ShaftGame*>(parentWidget())->IsPaused())
		return;

	if (nStatus == HUMAN_DROP)
		nImageId = ((++nImageId) == 5) ? 1 : nImageId;
	else if (nStatus == HUMAN_STAND)
		nImageId = 1;
	else if (nStatus == (HUMAN_LEFT | HUMAN_STAND))
		nImageId = ((++nImageId) == 5) ? 1 : nImageId;
	else if (nStatus == (HUMAN_RIGHT | HUMAN_STAND))
		nImageId = ((++nImageId) == 5) ? 1 : nImageId;
	else if (nStatus == (HUMAN_RIGHT | HUMAN_DROP))
		nImageId = ((++nImageId) == 5) ? 1 : nImageId;
	else if (nStatus == (HUMAN_LEFT | HUMAN_DROP))
		nImageId = ((++nImageId) == 5) ? 1 : nImageId;

	if (nWarnCount)
		nWarnCount--;

	update();
}

void Human::paintEvent(QPaintEvent *event)
{
	UNUSED_VARIABLE(event);

	QPainter painter(this);

	QString ImagePath;
	QPixmap Icon;

	if (nStatus == HUMAN_DROP)
		ImagePath.sprintf(":/man/drop%s/%d", (nWarnCount % 2) ? "_warn" : "", nImageId);
	else if (nStatus == HUMAN_STAND)
		ImagePath = (nWarnCount % 2) ? ":/man/stand_warn" : ":/man/stand";
	else if (nStatus == (HUMAN_RIGHT | HUMAN_STAND))
		ImagePath.sprintf(":/man/right%s/%d", (nWarnCount % 2) ? "_warn" : "", nImageId);
	else if (nStatus == (HUMAN_LEFT | HUMAN_STAND))
		ImagePath.sprintf(":/man/left%s/%d", (nWarnCount % 2) ? "_warn" : "", nImageId);
	else if (nStatus == (HUMAN_RIGHT | HUMAN_DROP))
		ImagePath.sprintf(":/man/drop_right%s/%d", (nWarnCount % 2) ? "_warn" : "", nImageId);
	else if (nStatus == (HUMAN_LEFT | HUMAN_DROP))
		ImagePath.sprintf(":/man/drop_left%s/%d", (nWarnCount % 2) ? "_warn" : "", nImageId);

	Icon.load(ImagePath);
	Icon.setMask(Icon.createMaskFromColor(QColor(0, 0, 255), Qt::MaskInColor));
	painter.drawPixmap(0, 0, Icon);
}
