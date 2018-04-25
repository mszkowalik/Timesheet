#include "MainWindow.h"
#include "TimeSpan.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	qRegisterMetaType<QList<Job> >("QList<Job>");
	QApplication a(argc, argv);
	MainWindow w;
	w.show();
	QObject::connect(&a, SIGNAL(aboutToQuit()), &w, SLOT(closing()));
	return a.exec();
}
