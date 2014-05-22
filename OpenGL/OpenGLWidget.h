#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H

#include "OpenGL/OpenGLData.h"
#include "Layers/LayerStack.h"
#include "Layers/MeshLayer.h"
#include "OpenGL/Shaders/SolidShader.h"
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

		void	InitializeTestMesh();

	signals:

	public slots:

};

#endif // OPENGLWIDGET_H
