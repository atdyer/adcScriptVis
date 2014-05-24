#ifndef FORT14IO_H
#define FORT14IO_H

#include <QObject>
#include <QRunnable>
#include <QFile>
#include <QTextStream>

#include "Adcirc/Data/AdcircData.h"
#include "Adcirc/Fort14.h"

class Fort14IO : public QObject, public QRunnable
{
		Q_OBJECT
	public:
		Fort14IO(Fort14 *fort14, QString fileLocation);
		~Fort14IO();

		void run();

	private:

		Fort14 *fort14;
		QString fileLoc;

	signals:

		void fort14Loaded(Fort14*);
		void progress(int);
		void progressStartValue(int);
		void progressEndValue(int);
		void readingInProgress(bool);

};

#endif // FORT14IO_H
