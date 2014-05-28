#ifndef FORT63_H
#define FORT63_H

#include <QObject>
#include <QFile>
#include <QProgressBar>
#include <QThread>

#include "Adcirc/Data/AdcircData.h"
#include "Adcirc/IO/Fort63IO.h"

class Fort63 : public QObject
{
		Q_OBJECT

		friend class Fort63IO;

	public:
		explicit Fort63(QObject *parent = 0);
		~Fort63();

		void	setReader(Fort63IO *newReader);

	private:

		QVector<float>	elevations;
		Fort63IO	*reader;

		QString		_gridID;
		int		_numDatasets;
		int		_numNodes;
		int		_outputInterval;
		float		_timestepSeconds;

	public slots:

		void	loadTimestep(int ts);


};

#endif // FORT63_H
