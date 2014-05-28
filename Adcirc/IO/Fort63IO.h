#ifndef FORT63IO_H
#define FORT63IO_H

#include <QObject>
#include <QFile>

#include "Adcirc/Data/AdcircData.h"
#include "Adcirc/Fort63.h"

class Fort63;
class Fort63IO : public QObject
{
		Q_OBJECT
	public:
		explicit Fort63IO(Fort63 *fort63, QString fileLocation);
		~Fort63IO();

	private:

		Fort63	*fort63;
		QFile	*file;
		QString	fileLoc;

	signals:

		void fort63Loaded(Fort63*);
		void progess(int);
		void progressStartValue(int);
		void progressEndValue(int);
		void readingInProgress(bool);
		void timestepFinishedReading(int);

	public slots:

		void initialize();

};

#endif // FORT63IO_H
