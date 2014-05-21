#ifndef LAYERSTACK_H
#define LAYERSTACK_H

#include <QObject>
#include <QMouseEvent>
#include <QWheelEvent>

#include "OpenGL/Cameras/GLCamera.h"
#include "OpenGL/Cameras/GLCamera2D.h"
#include "Layers/Layer.h"

class LayerStack : public QObject
{
		Q_OBJECT
	public:
		explicit LayerStack(QObject *parent = 0);

		void	appendLayer(Layer *layer);
		void	insertLayer(int i, Layer *layer);
		void	prependLayer(Layer *layer);
		void	removeLayer(int i);
		void	render();

		void	mouseMoveEvent(QMouseEvent *e);
		void	wheelEvent(QWheelEvent *e);


	private:

		GLCamera	*camera;
		QList<Layer*>	layers;

	signals:

	public slots:

};

#endif // LAYERSTACK_H