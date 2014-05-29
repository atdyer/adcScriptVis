#ifndef FORT63_H
#define FORT63_H

#include <QObject>
#include <QFile>
#include <QProgressBar>
#include <QThread>

#include "Adcirc/Data/AdcircData.h"

class Fort63IO;
class Fort63 : public QObject
{
		Q_OBJECT
		Q_PROPERTY(QString gridID READ getGridID WRITE setGridID)
		Q_PROPERTY(int numDatasets READ getNumDatasets)
		Q_PROPERTY(int numNodes READ getNumNodes)
		Q_PROPERTY(int outputInterval READ getOutputInterval)
		Q_PROPERTY(float timestepInSeconds READ getTimestepInSeconds)

		friend class Fort63IO;

	public:
		explicit Fort63(QObject *parent = 0);
		~Fort63();

		QString	getGridID();
		int	getNumDatasets();
		int	getNumNodes();
		int	getOutputInterval();
		float	getTimestepInSeconds();

		void	setGridID(QString newID);
		void	setReader(Fort63IO *newReader);

	private:

		int		currentTimestep;
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
