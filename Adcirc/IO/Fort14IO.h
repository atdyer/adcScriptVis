#ifndef FORT14IO_H
#define FORT14IO_H

#include <QObject>
#include <QRunnable>
#include <QFile>
#include <QTextStream>
#include <QProgressBar>

#include "Adcirc/Data/AdcircData.h"
#include "Adcirc/Fort14.h"

class Fort14IO : public QObject, public QRunnable
{
		Q_OBJECT
	public:
		Fort14IO(Fort14 *fort14, QString fileLocation, QProgressBar *progressBar = 0);
		~Fort14IO();

		void run();

	private:

		Fort14 *fort14;
		QString fileLoc;
		QProgressBar *progressBar;

	signals:

		void fort14Loaded(Fort14*);
		void progress(int);

};

#endif // FORT14IO_H
