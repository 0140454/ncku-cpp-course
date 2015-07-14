#include "MessagePanel.h"

MessagePanel::MessagePanel(QWidget *parent) : QWidget(parent)
{
	setVisible(false);
	resize(MESSAGE_PANEL_WIDTH, MESSAGE_PANEL_HEIGHT);
	move((WINDOW_WIDTH - MESSAGE_PANEL_WIDTH) / 2, (WINDOW_HEIGHT - MESSAGE_PANEL_HEIGHT) / 2);

	pNewGame = new QPushButton(this);
	pExit = new QPushButton(this);

	pNewGame->setText("新遊戲(&N)");
	pNewGame->setGeometry(203, 178, 100, 30);

	pExit->setText("結束本程式(&X)");
	pExit->setGeometry(16, 178, 100, 30);

	connect(pNewGame, SIGNAL(released()), this, SLOT(NewGame()));
	connect(pExit, SIGNAL(released()), this, SLOT(Exit()));
}

MessagePanel::~MessagePanel()
{
	delete pNewGame;
	delete pExit;
}

void MessagePanel::NewGame()
{
	QKeyEvent keyPress(QEvent::KeyPress, Qt::Key_N, Qt::ControlModifier);
	QCoreApplication::sendEvent(this, &keyPress);
}

void MessagePanel::Exit()
{
	QKeyEvent keyPress(QEvent::KeyPress, Qt::Key_X, Qt::ControlModifier);
	QCoreApplication::sendEvent(this, &keyPress);
}

void MessagePanel::paintEvent(QPaintEvent *event)
{
	UNUSED_VARIABLE(event);

	QPainter painter(this);

	raise();

	painter.drawPixmap(0, 0, QPixmap(":/images/message_panel"));
}

void MessagePanel::showEvent(QShowEvent *event)
{
	UNUSED_VARIABLE(event);

	pNewGame->setDefault(true);
	setFocus();
}

void MessagePanel::keyPressEvent(QKeyEvent *event)
{
	if (!event->isAutoRepeat())
	{
		if (event->key() == Qt::Key_Left)
		{
			pNewGame->setDefault(false);
			pExit->setDefault(true);
		}
		else if (event->key() == Qt::Key_Right)
		{
			pExit->setDefault(false);
			pNewGame->setDefault(true);
		}
		else if (event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return)
		{
			if (pExit->isDefault())
				Exit();
			else
				NewGame();
		}
	}
}
