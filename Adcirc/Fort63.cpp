#include "Adcirc/IO/Fort63IO.h"
#include "Fort63.h"

Fort63::Fort63(QObject *parent) :
	QObject(parent)
{
	setObjectName("fort63");

	reader = 0;
	_gridID = "None";
	_numDatasets = 0;
	_numNodes = 0;
	_outputInterval = 0;
	_timestepSeconds = 0.0;
}


Fort63::~Fort63()
{

}


QVector<float> *Fort63::getElevations()
{
	return &elevations;
}


QString Fort63::getGridID()
{
	return _gridID;
}


int Fort63::getNumDatasets()
{
	return _numDatasets;
}


int Fort63::getNumNodes()
{
	return _numNodes;
}


int Fort63::getOutputInterval()
{
	return _outputInterval;
}


float Fort63::getTimestepInSeconds()
{
	return _timestepSeconds;
}


void Fort63::setGridID(QString newID)
{
	_gridID = newID;
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
