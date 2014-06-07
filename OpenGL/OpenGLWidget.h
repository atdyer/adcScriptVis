#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H

#include "OpenGL/OpenGLData.h"
#include "Layers/LayerStack.h"
#include "Layers/MeshLayer.h"

#include <QtDebug>

class OpenGLWidget : public QGLWidget
{
		Q_OBJECT
	public:
		explicit OpenGLWidget(QWidget *parent = 0);

		void	initializeGL();
		void	resizeGL(int w, int h);
		void	paintGL();
		void	setCurrentLayerStack(LayerStack *newStack);

		GLCamera	*getCurrentCamera();
		GLCamera2D	*getCurrent2DCamera();
		GLCamera3D	*getCurrent3DCamera();

	protected:

		void	mouseMoveEvent(QMouseEvent *e);
		void	mousePressEvent(QMouseEvent *e);
		void	mouseReleaseEvent(QMouseEvent *e);
		void	keyPressEvent(QKeyEvent *e);
		void	wheelEvent(QWheelEvent *e);

	private:

		LayerStack	*currentLayerStack;

	signals:

	public slots:

		void	refresh();
		void	reset();
		void	panCamera(float dx, float dy);
		void	rotateCamera(float degrees);
		void	tiltCamera(float degrees);
		void	use2DCamera();
		void	use3DCamera();
		void	zoomCamera(int direction, float scale);

};

#endif // OPENGLWIDGET_H
