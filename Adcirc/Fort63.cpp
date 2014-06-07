#include "Adcirc/IO/Fort63IO.h"
#include "Fort63.h"

Fort63::Fort63(QObject *parent) :
	QObject(parent)
{
	setObjectName("fort63");

	reader = 0;

	currentTimestep = 0;
	gridID = "None";
	numDatasets = 0;
	numNodes = 0;
	outputInterval = 0;
	timestepSeconds = 0.0;
}


Fort63::~Fort63()
{

}


QVector<float> *Fort63::getElevations()
{
	return &elevations;
}


int Fort63::getCurrentTimestep()
{
	return currentTimestep;
}


QString Fort63::getGridID()
{
	return gridID;
}


int Fort63::getNumDatasets()
{
	return numDatasets;
}


int Fort63::getNumNodes()
{
	return numNodes;
}


int Fort63::getOutputInterval()
{
	return outputInterval;
}


float Fort63::getTimestepInSeconds()
{
	return timestepSeconds;
}


void Fort63::setCurrentTimestep(int ts)
{
	loadTimestep(ts);
}


void Fort63::setGridID(QString newID)
{
	gridID = newID;
}


void Fort63::setReader(Fort63IO *newReader)
{
	reader = newReader;
	connect(reader, SIGNAL(timestepLoaded(Fort63*,int)), this, SIGNAL(timestepLoaded(Fort63*,int)));
}


void Fort63::loadTimestep(int ts)
{
	QMetaObject::invokeMethod(reader, "loadTimestep", Q_ARG(int, ts));
}
