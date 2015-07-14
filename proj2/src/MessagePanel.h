#ifndef MESSAGEPANEL_H
#define MESSAGEPANEL_H
#include <QtWidgets>
#include <QKeyEvent>
#include "Common.h"

class MessagePanel : public QWidget{
	Q_OBJECT

public:
	MessagePanel(QWidget *parent = 0);
	virtual ~MessagePanel();

protected slots:
	void NewGame();
	void Exit();

protected:
	virtual void paintEvent(QPaintEvent *event);
	virtual void showEvent(QShowEvent *event);
	virtual void keyPressEvent(QKeyEvent *event);

private:
	QPushButton *pNewGame;
	QPushButton *pExit;
};
#endif // MESSAGEPANEL_H
