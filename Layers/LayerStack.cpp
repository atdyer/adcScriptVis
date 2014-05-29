#include "LayerStack.h"

LayerStack::LayerStack(QObject *parent) :
	QObject(parent)
{
	cam2D = new GLCamera2D(this);
	cam3D = new GLCamera3D(this);
	camera = cam2D;
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
	if (cam2D)
		cam2D->setViewportSize(w, h);
	if (cam3D)
		cam3D->setViewportSize(w, h);
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


GLCamera *LayerStack::getCurrentCamera()
{
	return camera;
}


GLCamera2D *LayerStack::get2DCamera()
{
	return cam2D;
}


GLCamera3D *LayerStack::get3DCamera()
{
	return cam3D;
}


void LayerStack::resetCamera()
{
	if (camera)
		camera->reset();
	emit updateGL();
}


void LayerStack::use2DCamera()
{
	camera = cam2D;
	for (int i=0; i<layers.size(); ++i)
		layers[i]->setCamera(camera);
	emit updateGL();
}


void LayerStack::use3DCamera()
{
	camera = cam3D;
	for (int i=0; i<layers.size(); ++i)
		layers[i]->setCamera(camera);
	emit updateGL();
}
