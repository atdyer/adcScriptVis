#ifndef FORT14_H
#define FORT14_H

#include <QObject>
#include <QVector>

#include "Adcirc/Data/AdcircData.h"

class Fort14 : public QObject
{
		Q_OBJECT
		Q_PROPERTY(QString gridID READ getGridID WRITE setGridID)
		Q_PROPERTY(int numNodes READ getNumNodes)
		Q_PROPERTY(int numElements READ getNumElements)

		friend class Fort14IO;

	public:
		explicit Fort14(QObject *parent = 0);

		QVector<Element>	*getElements();
		QString			getGridID();
		QVector<Node>		*getNodes();
		int			getNumNodes();
		int			getNumElements();

		void	setGridID(QString newID);

	private:

		QString	_gridID;
		int	_numNodes;
		int	_numElements;

		QVector<Node>		nodes;
		QVector<Element>	elements;

	signals:

	public slots:	

};

#endif // FORT14_H
