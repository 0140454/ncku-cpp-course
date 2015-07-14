#include "ShaftGame.h"
#include "MainWindow.h"
#include <ctime>
#include <QSound>

ShaftGame::ShaftGame(QWidget *parent) : QWidget(parent)
{
	srand(time(NULL));

	setFocus();
	resize(WINDOW_WIDTH, WINDOW_HEIGHT);

	InitStairs();

	nBackgroundOffset = 0;
	nLastPressKey = 0;
	nLastTime = time(NULL);
	bGameOver = false;
	bPaused = false;
	nElapsedTime = 0;
	nBackgroudInterval = 16;
	nHumanLife = 120;
	pHuman = new Human(stairs[stairs.size() - 2]->GetRealTimePos().x(),
						stairs[stairs.size() - 2]->GetRealTimePos().y() - HUMAN_HEIGHT, this);
	pSpiked = new Spiked(this);
	pScorePanel = new ScorePanel(this);
	pMessagePanel = new MessagePanel(this);

	setting = new QSettings("cpp_proj2", "shaft");

	nBackgroundTimerId = startTimer(nBackgroudInterval);
	nHumanTimerId = startTimer(8);
}

ShaftGame::~ShaftGame()
{
	delete pSpiked;
	delete pHuman;
	delete pScorePanel;
	delete pMessagePanel;
	delete setting;

	for (int i = 0; i < stairs.size(); i++)
		delete stairs[i];
	stairs.clear();
}

void ShaftGame::InitStairs()
{
	for (int i = HUMAN_HEIGHT; i < this->height(); i += HUMAN_HEIGHT + STAIR_STAND_HEIGHT)
		stairs.push_back(GenStair(i, this));

	Stair *pTmp = new StairNormal(stairs[stairs.size() - 2]->GetRealTimePos().y(), this);

	delete stairs[stairs.size() - 2];
	stairs[stairs.size() - 2] = pTmp;
}

bool ShaftGame::IsPaused()
{
	return bPaused;
}

void ShaftGame::SetPaused(bool bEnabled)
{
	bPaused = bEnabled;
}

bool ShaftGame::IsGameOver()
{
	return bGameOver;
}

void ShaftGame::timerEvent(QTimerEvent *event)
{
	if (IsPaused() && nHumanLife >= 0)
		return;

	if (event->timerId() == nBackgroundTimerId)
	{
		nBackgroundOffset++;

		for (int i = 0; i < stairs.size(); i++)
		{
			stairs[i]->Update();
			stairs[i]->show();
		}
		if (stairs[0]->pos().y() + stairs[0]->height() <= 0)
		{
			delete stairs[0];
			stairs.pop_front();
		}

		if (stairs.size() && height() - stairs.back()->GetRealTimePos().y() >= HUMAN_HEIGHT + STAIR_STAND_HEIGHT)
			stairs.push_back(GenStair(stairs.back()->GetRealTimePos().y() + HUMAN_HEIGHT + STAIR_STAND_HEIGHT, this));

		pSpiked->raise();

		if (pHuman)
			nHumanLife += pHuman->Update();
	}
	else if (event->timerId() == nHumanTimerId)
	{
		if (!(pHuman->GetStatus() & HUMAN_STAND) || pHuman->GetStatus() & HUMAN_LEFT || pHuman->GetStatus() & HUMAN_RIGHT)
			nHumanLife += pHuman->Update(true);

		if (pHuman->pos().y() >= height())
			nHumanLife = 0;

		if (time(NULL) != nLastTime)
		{
			nElapsedTime++;
			nLastTime = time(NULL);

			if (nElapsedTime % 3 == 0)
				(*pScorePanel)++;

			if (nElapsedTime && (nElapsedTime % 20 == 0))
			{
				if (nBackgroudInterval > 8)
				{
					killTimer(nBackgroundTimerId);
					nBackgroundTimerId = startTimer(--nBackgroudInterval);
				}
			}
		}
	}

	if (nHumanLife > 120)
		nHumanLife = 120;
	else if (nHumanLife <= 0)
	{
		if (event->timerId() != nBackgroundTimerId)
		{
			killTimer(nHumanTimerId);

			if (pHuman)
			{
				delete pHuman;
				pHuman = NULL;
			}

			if (!bGameOver)
			{
				bGameOver = true;
				dynamic_cast<MainWindow*>(parentWidget())->ResetMenu();

				if (nHumanLife > -50)
					QSound::play(":/sounds/dead");

				pMessagePanel->show();
			}

			nHumanLife = 0;
		}
	}

	update();
}

void ShaftGame::SetGameOver()
{
	nHumanLife = -100;
}

int ShaftGame::GetHumanLife()
{
	return nHumanLife;
}

void ShaftGame::keyPressEvent(QKeyEvent *event)
{
	if (IsPaused())
		return;

	if (!event->isAutoRepeat())
	{
		if (pHuman)
		{
			switch(event->key())
			{
			case Qt::Key_Left:
				pHuman->SetDirection(HUMAN_LEFT);
				nLastPressKey = event->key();
				break;
			case Qt::Key_Right:
				pHuman->SetDirection(HUMAN_RIGHT);
				nLastPressKey = event->key();
				break;
			default:
				break;
			}
		}

		update();
	}

	QWidget::keyPressEvent(event);
}

void ShaftGame::keyReleaseEvent(QKeyEvent *event)
{
	if (IsPaused())
		return;

	if (!event->isAutoRepeat())
	{
		if (pHuman)
		{
			if (nLastPressKey == event->key())
			{
				pHuman->SetDirection();
				nLastPressKey = 0;
				update();
			}
		}
	}

	QWidget::keyReleaseEvent(event);
}

void ShaftGame::paintEvent(QPaintEvent *event)
{
	UNUSED_VARIABLE(event);

	QPainter painter(this);

	if (nBackgroundOffset >= BACKGROUND_HEIGHT)
		nBackgroundOffset -= BACKGROUND_HEIGHT;

	/// Background
	// left
	painter.drawTiledPixmap(0, -nBackgroundOffset,
							WINDOW_WIDTH - INFO_WIDTH, WINDOW_HEIGHT + nBackgroundOffset,
							QPixmap(":/images/background"));
	// right
	painter.drawTiledPixmap(WINDOW_WIDTH - INFO_WIDTH, 0,
							WINDOW_WIDTH, WINDOW_HEIGHT,
							QPixmap(":/images/info"));
	/// Side
	// left
	painter.drawTiledPixmap(0, -nBackgroundOffset,
							SIDE_WIDTH, WINDOW_HEIGHT + nBackgroundOffset,
							QPixmap(":/images/side"));
	// right
	painter.drawTiledPixmap(WINDOW_WIDTH - INFO_WIDTH - SIDE_WIDTH, -nBackgroundOffset,
							SIDE_WIDTH, WINDOW_HEIGHT + nBackgroundOffset,
							QPixmap(":/images/side"));

	/// Stair for spiked
	for (QList<Stair*>::iterator i = stairs.begin(); i != stairs.end(); i++)
	{
		if (dynamic_cast<StairSpiked*>(*i))
		{
			QPixmap SpikedUp(":/stairs/spiked/up");

			SpikedUp.setMask(SpikedUp.createMaskFromColor(QColor(0, 0, 255), Qt::MaskInColor));
			painter.drawPixmap((*i)->GetRealTimePos().x(), (*i)->GetRealTimePos().y() - STAIR_STAND_HEIGHT, SpikedUp);
		}
	}

	/// Life
	QString ImagePath;
	QPixmap HpImage, LifeImage;

	ImagePath.sprintf(":/life/%d", (nHumanLife < 0) ? 0 : (nHumanLife / 10));
	HpImage.load(ImagePath);
	LifeImage.load(":/life/label");

	LifeImage.setMask(LifeImage.createMaskFromColor(QColor(0, 0, 255), Qt::MaskInColor));
	painter.drawPixmap(WINDOW_WIDTH - INFO_WIDTH + EDGE_OFFSET, EDGE_OFFSET, LifeImage);
	painter.drawPixmap(WINDOW_WIDTH - INFO_WIDTH + EDGE_OFFSET * 2, EDGE_OFFSET * 2, HpImage);

	/// Best score
	QString BestScore;

	painter.setPen(QColor(255, 255, 255));
	painter.setFont(QFont(QString::fromLocal8Bit("Arial"), 12, QFont::Bold));

	if (setting->value("best", 0).toInt() < pScorePanel->GetFloor())
		setting->setValue("best", pScorePanel->GetFloor());

	BestScore.sprintf("%04d", setting->value("best", 0).toInt());
	painter.drawText(WINDOW_WIDTH - INFO_WIDTH + EDGE_OFFSET, EDGE_OFFSET * 7, "最佳紀錄");
	painter.drawText(WINDOW_WIDTH - INFO_WIDTH + EDGE_OFFSET * 2, EDGE_OFFSET * 8, "地下 " + BestScore + " 階");
}
