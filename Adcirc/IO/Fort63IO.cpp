#include "Fort63IO.h"

Fort63IO::Fort63IO(Fort63 *fort63, QString fileLocation) :
	QObject()
{
	this->fort63 = fort63;
	this->file = 0;
	this->fileLoc = fileLocation;
	this->fileMapped = false;
}


Fort63IO::~Fort63IO()
{
	qDebug() << "Deleting reader" << thread();
}


void Fort63IO::mapFile()
{
	qDebug() << "Mapping fort.63";
}


void Fort63IO::initialize()
{
	mapFile();
	loadTimestep(1);
}


void Fort63IO::loadTimestep(int ts)
{
	qDebug() << "Loading timestep " << ts << " on thread: " << thread();
	emit fort63Loaded(fort63, ts);
}
