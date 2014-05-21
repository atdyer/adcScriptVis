#include "GLCamera2D.h"

GLCamera2D::GLCamera2D(QObject *parent) :
	GLCamera(parent)
{
}


void GLCamera2D::mouseMoveEvent(QMouseEvent *e)
{
	if (e->buttons() == Qt::LeftButton)
	{
		// Pan the camera
		ModelViewMatrix.translate(e->x(), e->y());
	}
}


void GLCamera2D::wheelEvent(QWheelEvent *e)
{
	ProjectionMatrix.scale(e->delta());
}
