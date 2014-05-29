#include "GLCamera3D.h"

GLCamera3D::GLCamera3D(QObject *parent) :
	QObject(parent),
	GLCamera()
{
	setObjectName("cam3D");

	width = 0;
	height = 0;

	pixelToViewRatio = 1.0;

	dx = 0.0;
	dy = 0.0;
	newX = 0;
	newY = 0;
	oldX = 0;
	oldY = 0;

	panX = 0.0;
	panY = 0.0;
	panZ = 0.0;

	xRot = 0.0;
	zRot = 0.0;

	zoom = 1.0;
	zoomScale = 1.1;
}


const float *GLCamera3D::getMVP()
{
	MVPMatrix.setToIdentity();
	MVPMatrix.ortho(-1.0*width/height, 1.0*width/height, -1.0, 1.0, -1.0*zoom, 1.0*zoom);
	MVPMatrix.scale(zoom);
	MVPMatrix.rotate(xRot, 1.0, 0.0, 0.0);
	MVPMatrix.rotate(zRot, 0.0, 0.0, 1.0);
	MVPMatrix.translate(panX, panY, panZ);

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

		rotateCamera(dx/6.0);
		tiltCamera(dy/6.0);

		oldX = newX;
		oldY = newY;
	}
	else if (e->buttons() == Qt::RightButton)
	{
		newX = e->x();
		newY = e->y();

		dx = newX-oldX;
		dy = newY-oldY;

		panCamera(dx, dy);

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
	panX = 0.0;
	panY = 0.0;
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
	zoomCamera(e->delta(), zoomScale);
}


void GLCamera3D::panCamera(float dx, float dy)
{
	float rads = qDegreesToRadians(zRot);
	float c = cos(rads);
	float s = sin(rads);
	float scalingRatio = pixelToViewRatio/zoom;

	panX += scalingRatio * (dx*c - dy*s);
	panY -= scalingRatio * (dx*s + dy*c);
//	panZ += scalingRatio * dy * sin(qDegreesToRadians(xRot));
}


void GLCamera3D::rotateCamera(float degrees)
{
	zRot += degrees;
}


void GLCamera3D::tiltCamera(float degrees)
{
	xRot += degrees;
}


void GLCamera3D::zoomCamera(int direction, float scale)
{
	if (direction > 0)
		zoom *= scale;
	else if (direction < 0)
		zoom /= scale;
}
