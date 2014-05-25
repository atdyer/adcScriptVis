#include "GLCamera3D.h"

GLCamera3D::GLCamera3D(QObject *parent) :
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

	xRot = 0.0;
	zRot = 0.0;

	zoom = 1.0;
	zoomScale = 1.1;
}


const float *GLCamera3D::getMVP()
{
	MVPMatrix.setToIdentity();
	MVPMatrix.ortho(-1.0*width/height, 1.0*width/height, -1.0, 1.0, -1000000.0, 1000000.0);
	MVPMatrix.scale(zoom);
	MVPMatrix.translate(panX, panY);
	MVPMatrix.rotate(xRot, 1.0, 0.0, 0.0);
	MVPMatrix.rotate(zRot, 0.0, 0.0, 1.0);

	return MVPMatrix.data();
}


void GLCamera3D::mouseMoveEvent(QMouseEvent *e)
{
	if (e->buttons() == Qt::LeftButton)
	{
		newX = e->x();
		newY = e->y();

		dx = newX-oldX;
		dy = newY-oldY;

		zRot += dx;
		xRot += dy;

		oldX = newX;
		oldY = newY;
	}
	else if (e->buttons() == Qt::RightButton)
	{
		newX = e->x();
		newY = e->y();

		dx = newX-oldX;
		dy = newY-oldY;

		panX += pixelToViewRatio*dx/zoom;
		panY -= pixelToViewRatio*dy/zoom;

		oldX = newX;
		oldY = newY;
	}
}


void GLCamera3D::mousePressEvent(QMouseEvent *e)
{
	oldX = e->x();
	oldY = e->y();
}


void GLCamera3D::mouseReleaseEvent(QMouseEvent *)
{

}


void GLCamera3D::reset()
{
	zoom = 1.0;
	xRot = 0.0;
	zRot = 0.0;
}


void GLCamera3D::setViewportSize(int w, int h)
{
	width = w;
	height = h;

	pixelToViewRatio = 2.0/height;
}


void GLCamera3D::wheelEvent(QWheelEvent *e)
{
	if (e->delta() > 0)
		zoom *= zoomScale;
	else
		zoom /= zoomScale;
}
