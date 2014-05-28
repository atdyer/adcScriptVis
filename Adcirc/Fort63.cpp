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
	_timestepSeconds = 0;
}


Fort63::~Fort63()
{

}


void Fort63::setReader(Fort63IO *newReader)
{
	reader = newReader;
}


void Fort63::loadTimestep(int ts)
{
	QMetaObject::invokeMethod(reader, "loadTimestep", Q_ARG(int, ts));
}
