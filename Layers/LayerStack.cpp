#include "LayerStack.h"

LayerStack::LayerStack(QObject *parent) :
	QObject(parent)
{
	camera = new GLCamera2D(this);
}


void LayerStack::appendLayer(Layer *layer)
{
	layers.append(layer);
}


void LayerStack::insertLayer(int i, Layer *layer)
{
	layers.insert(i, layer);
}


void LayerStack::prependLayer(Layer *layer)
{
	layers.prepend(layer);
}


void LayerStack::removeLayer(int i)
{
	if (i >= 0 && i < layers.size())
		layers.removeAt(i);
}


void LayerStack::render()
{
	for (int i=0; i<layers.size(); ++i)
		layers[i]->render();
}


void LayerStack::mouseMoveEvent(QMouseEvent *e)
{
	if (camera)
		camera->mouseMoveEvent(e);
}


void LayerStack::wheelEvent(QWheelEvent *e)
{
	if (camera)
		camera->wheelEvent(e);
}
