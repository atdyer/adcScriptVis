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
		Q_PROPERTY(int currentTimestep READ getCurrentTimestep WRITE setCurrentTimestep)
		Q_PROPERTY(int numDatasets READ getNumDatasets)
		Q_PROPERTY(int numNodes READ getNumNodes)
		Q_PROPERTY(int outputInterval READ getOutputInterval)
		Q_PROPERTY(float timestepInSeconds READ getTimestepInSeconds)

		friend class Fort63IO;

	public:
		explicit Fort63(QObject *parent = 0);
		~Fort63();

		QVector<float>	*getElevations();
		int		getCurrentTimestep();
		QString		getGridID();
		int		getNumDatasets();
		int		getNumNodes();
		int		getOutputInterval();
		float		getTimestepInSeconds();

		void		setCurrentTimestep(int ts);
		void		setGridID(QString newID);
		void		setReader(Fort63IO *newReader);

	private:

		QVector<float>	elevations;
		Fort63IO	*reader;

		int		currentTimestep;
		QString		gridID;
		int		numDatasets;
		int		numNodes;
		int		outputInterval;
		float		timestepSeconds;

	signals:

		void	timestepLoaded(Fort63*, int);

	public slots:

		void	loadTimestep(int ts);


};

#endif // FORT63_H
