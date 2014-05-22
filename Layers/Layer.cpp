#include "Layer.h"

Layer::Layer()
{
	camera = 0;
}


void Layer::setCamera(GLCamera *newCamera)
{
	camera = newCamera;
}
