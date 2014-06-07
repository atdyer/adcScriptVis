#ifndef FORT14_H
#define FORT14_H

#include <QObject>
#include <QVector>

#include "Adcirc/Data/AdcircData.h"

class Fort14 : public QObject
{
		Q_OBJECT
		Q_PROPERTY(QString gridID READ getGridID WRITE setGridID)
		Q_PROPERTY(float maxElevation READ getMaxZ)
		Q_PROPERTY(float minElevation READ getMinZ)
		Q_PROPERTY(int numNodes READ getNumNodes)
		Q_PROPERTY(int numElements READ getNumElements)

		friend class Fort14IO;

	public:
		explicit Fort14(QObject *parent = 0);

		QVector<Element>	*getElements();
		QString			getGridID();
		QVector<Node>		*getNodes();
		float			getMaxZ();
		float			getMinZ();
		int			getNumNodes();
		int			getNumElements();

		void	setGridID(QString newID);

	private:

		QString	gridID;
		float	minZ;
		float	maxZ;
		int	numNodes;
		int	numElements;

		QVector<Node>		nodes;
		QVector<Element>	elements;

	signals:

	public slots:	

};

#endif // FORT14_H
