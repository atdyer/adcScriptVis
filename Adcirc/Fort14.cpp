#include "Fort14.h"

Fort14::Fort14(QObject *parent) :
	QObject(parent)
{
	setObjectName("fort14");

	_gridID = "None";
	_numNodes = 10;
	_numElements = 5;
}

QVector<Element> *Fort14::getElements()
{
	return &elements;
}

QString Fort14::getGridID()
{
	return _gridID;
}

QVector<Node> *Fort14::getNodes()
{
	return &nodes;
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
