#include <QApplication>
#include <QTextCodec>
#include <QSplashScreen>
#include <QTimer>
#include "MainWindow.h"

int main(int argc, char* argv[])
{
	QApplication app(argc, argv);

	MainWindow mw;
	QSplashScreen splash;

	splash.setPixmap(QPixmap(":/images/welcome"));
	splash.show();

	QTimer::singleShot(2500, &splash, SLOT(close()));
	QTimer::singleShot(2500, &mw, SLOT(show()));

	return app.exec();
}
