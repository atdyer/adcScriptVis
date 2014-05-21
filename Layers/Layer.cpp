#include "Layer.h"

Layer::Layer(QObject *parent) :
	QObject(parent)
{
	camera = 0;
}


void Layer::setCamera(GLCamera *newCamera)
{
	camera = newCamera;
}
