#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H

#include "OpenGL/OpenGLData.h"
#include "Layers/LayerStack.h"
#include <QtDebug>

class OpenGLWidget : public QGLWidget
{
		Q_OBJECT
	public:
		explicit OpenGLWidget(QWidget *parent = 0);

		void	initializeGL();
		void	resizeGL(int w, int h);
		void	paintGL();

	protected:

		void	mouseMoveEvent(QMouseEvent *e);
		void	wheelEvent(QWheelEvent *e);

	private:

		LayerStack	*currentLayerStack;

	signals:

	public slots:

};

#endif // OPENGLWIDGET_H
