#include "Fort14.h"

Fort14::Fort14(QObject *parent) :
	QObject(parent)
{
	setObjectName("fort14");

	gridID = "None";
	maxZ = 1.0;
	minZ = 0.0;
	numNodes = 10;
	numElements = 5;
}

QVector<Element> *Fort14::getElements()
{
	return &elements;
}

QString Fort14::getGridID()
{
	return gridID;
}

float Fort14::getMaxZ()
{
	return maxZ;
}

float Fort14::getMinZ()
{
	return minZ;
}

QVector<Node> *Fort14::getNodes()
{
	return &nodes;
}

int Fort14::getNumNodes()
{
	return numNodes;
}

int Fort14::getNumElements()
{
	return numElements;
}

void Fort14::setGridID(QString newID)
{
	gridID = newID;
}
