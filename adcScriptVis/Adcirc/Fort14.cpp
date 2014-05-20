#include "Fort14.h"

Fort14::Fort14(QObject *parent) :
	QObject(parent)
{
	setObjectName("fort14");
}


int Fort14::numNodes()
{
	return 50;
}

int Fort14::numElements()
{
	return 100;
}
