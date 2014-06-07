#ifndef LAYERSTACK_H
#define LAYERSTACK_H

#include <QObject>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QWheelEvent>

#include "OpenGL/Cameras/GLCamera.h"
#include "OpenGL/Cameras/GLCamera2D.h"
#include "OpenGL/Cameras/GLCamera3D.h"
#include "Layers/Layer.h"
#include "Layers/MeshLayerAdcirc.h"

class LayerStack : public QObject
{
		Q_OBJECT
	public:
		explicit LayerStack(QObject *parent = 0);

		void	appendLayer(Layer *layer);
		void	appendLayer(MeshLayerAdcirc *layer);
		void	insertLayer(int i, Layer *layer);
		void	insertLayer(int i, MeshLayerAdcirc *layer);
		void	prependLayer(Layer *layer);
		void	prependLayer(MeshLayerAdcirc *layer);
		void	removeLayer(int i);
		void	render();

		void	setViewportSize(int w, int h);
		void	mouseMoveEvent(QMouseEvent *e);
		void	mousePressEvent(QMouseEvent *e);
		void	mouseReleaseEvent(QMouseEvent *e);
		void	keyPressEvent(QKeyEvent *e);
		void	wheelEvent(QWheelEvent *e);


		GLCamera	*getCurrentCamera();
		GLCamera2D	*get2DCamera();
		GLCamera3D	*get3DCamera();


	private:

		GLCamera	*camera;
		GLCamera2D	*cam2D;
		GLCamera3D	*cam3D;
		QList<Layer*>	layers;

	signals:

		void	updateGL();

	public slots:

		void	resetCamera();
		void	use2DCamera();
		void	use3DCamera();

};

#endif // LAYERSTACK_H
