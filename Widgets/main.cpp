#include "MainWindow.h"
#include <QApplication>
#include <QFile>
#include <QTextStream>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	QCoreApplication::setOrganizationName("ncsu");
	QCoreApplication::setOrganizationDomain("ncsu.edu");
	QCoreApplication::setApplicationName("adcScriptVis");

	QFile f(":qdarkstyle/style.qss");
	if (f.exists())
	{
		f.open(QFile::ReadOnly | QFile::Text);
		QTextStream ts(&f);
		a.setStyleSheet(ts.readAll());
	}

	MainWindow w;
	w.show();

	return a.exec();
}
