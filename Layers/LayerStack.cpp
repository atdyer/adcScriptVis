#include "LayerStack.h"

LayerStack::LayerStack(QObject *parent) :
	QObject(parent)
{
	camera = new GLCamera3D(this);
}


void LayerStack::appendLayer(Layer *layer)
{
	if (layer)
	{
		layer->setCamera(camera);
		layers.append(layer);
	}
}


void LayerStack::insertLayer(int i, Layer *layer)
{
	if (layer)
	{
		layer->setCamera(camera);
		layers.insert(i, layer);
	}
}


void LayerStack::prependLayer(Layer *layer)
{
	if (layer)
	{
		layer->setCamera(camera);
		layers.prepend(layer);
	}
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


void LayerStack::setViewportSize(int w, int h)
{
	if (camera)
		camera->setViewportSize(w, h);
	emit updateGL();
}


void LayerStack::mouseMoveEvent(QMouseEvent *e)
{
	if (camera)
		camera->mouseMoveEvent(e);
	emit updateGL();
}


void LayerStack::mousePressEvent(QMouseEvent *e)
{
	if (camera)
		camera->mousePressEvent(e);
	emit updateGL();
}


void LayerStack::mouseReleaseEvent(QMouseEvent *e)
{
	if (camera)
		camera->mouseReleaseEvent(e);
	emit updateGL();
}


void LayerStack::wheelEvent(QWheelEvent *e)
{
	if (camera)
		camera->wheelEvent(e);
	emit updateGL();
}
