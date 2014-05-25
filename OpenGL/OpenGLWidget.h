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

	protected:

		void	mouseMoveEvent(QMouseEvent *e);
		void	mousePressEvent(QMouseEvent *e);
		void	mouseReleaseEvent(QMouseEvent *e);
		void	wheelEvent(QWheelEvent *e);

	private:

		LayerStack	*currentLayerStack;

	signals:

	public slots:

		void	reset();
		void	use2DCamera();
		void	use3DCamera();

};

#endif // OPENGLWIDGET_H
