#ifndef FORT63IO_H
#define FORT63IO_H

#include <QObject>
#include <QFile>
#include <QThread>
#include <QDebug>
#include <QMap>

#include "Adcirc/Data/AdcircData.h"
#include "Adcirc/Fort63.h"

class Fort63IO : public QObject
{
		Q_OBJECT
	public:
		explicit Fort63IO(Fort63 *fort63, QString fileLocation);
		~Fort63IO();

	private:

		Fort63			*fort63;
		QFile			*file;
		QTextStream		fileStream;
		QString			fileLoc;
		bool			fileInitialized;
		bool			fileMapped;
		QMap<int, qint64>	map;
		qint64			timestepSize;

		void mapFile();
		bool verifyHeader(int ts, QString header);

	signals:

		void fort63Loaded(Fort63*);
		void progress(int);
		void progressStartValue(int);
		void progressEndValue(int);
		void readingInProgress(bool);
		void timestepLoaded(Fort63*, int);

	public slots:

		void initialize();
		void loadTimestep(int ts);

};

#endif // FORT63IO_H
