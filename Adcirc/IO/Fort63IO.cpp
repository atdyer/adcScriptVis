#include "Fort63IO.h"

Fort63IO::Fort63IO(Fort63 *fort63, QString fileLocation) :
	QObject()
{
	this->fort63 = fort63;
	this->file = 0;
	this->fileLoc = fileLocation;
}


Fort63IO::~Fort63IO()
{
}


void Fort63IO::initialize()
{

}
