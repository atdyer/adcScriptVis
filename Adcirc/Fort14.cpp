#include "Fort14.h"

Fort14::Fort14(QObject *parent) :
	QObject(parent)
{
	setObjectName("fort14");

	_gridID = "None";
	_numNodes = 10;
	_numElements = 5;
}

QString Fort14::getGridID()
{
	return _gridID;
}

int Fort14::getNumNodes()
{
	return _numNodes;
}

int Fort14::getNumElements()
{
	return _numElements;
}

void Fort14::setGridID(QString newID)
{
	_gridID = newID;
}
