#include "GLCamera2D.h"

GLCamera2D::GLCamera2D(QObject *parent) :
	QObject(parent),
	GLCamera()
{

	width = 0;
	height = 0;

	pixelToViewRatio = 1.0;

	dx = 0.0;
	dy = 0.0;
	newX = 0;
	newY = 0;
	oldX = 0;
	oldY = 0;

	zoom = 1.0;
	zoomScale = 1.1;
}


const float *GLCamera2D::getMVP()
{
	MVPMatrix.setToIdentity();
	MVPMatrix.ortho(-1.0*width/height, 1.0*width/height, -1.0, 1.0, -1000000.0, 1000000.0);
	MVPMatrix.scale(zoom);
	MVPMatrix.translate(dx, dy);
	return MVPMatrix.data();
}


void GLCamera2D::mouseMoveEvent(QMouseEvent *e)
{
	if (e->buttons() == Qt::LeftButton)
	{
		newX = e->x();
		newY = e->y();

		dx += pixelToViewRatio*(newX - oldX)/zoom;
		dy -= pixelToViewRatio*(newY - oldY)/zoom;

		oldX = newX;
		oldY = newY;
	}
}


void GLCamera2D::mousePressEvent(QMouseEvent *e)
{
	oldX = e->x();
	oldY = e->y();
}


void GLCamera2D::mouseReleaseEvent(QMouseEvent *)
{

}


void GLCamera2D::reset()
{
	zoom = 1.0;
	dx = 0;
	dy = 0;
}


void GLCamera2D::setViewportSize(int w, int h)
{
	width = w;
	height = h;

	pixelToViewRatio = 2.0/height;
}


void GLCamera2D::wheelEvent(QWheelEvent *e)
{
	if (e->delta() > 0)
		zoom *= zoomScale;
	else
		zoom /= zoomScale;
}
