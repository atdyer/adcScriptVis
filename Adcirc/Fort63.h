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

	private:

		QVector<float>	elevations;

		QString	_gridID;
		int	_numDatasets;
		int	_numNodes;
		int	_outputInterval;
		float	_timestepSeconds;

		QThread	workerThread;


	signals:

		void	initialized(Fort63*);
		void	timestepLoaded(int ts);

	public slots:

		void	setPath(QString fileLocation, QProgressBar *progressBar = 0);

	protected slots:

		void	timestepFinishedReading(int ts);

};

#endif // FORT63_H
