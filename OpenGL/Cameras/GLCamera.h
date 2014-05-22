#ifndef GLCAMERA_H
#define GLCAMERA_H

#include <QMatrix4x4>
#include <QMouseEvent>
#include <QWheelEvent>

class GLCamera
{
	public:
		GLCamera();

		virtual const float	*getMVP();

		virtual void	mouseMoveEvent(QMouseEvent *e) = 0;
		virtual void	mousePressEvent(QMouseEvent *e) = 0;
		virtual void	mouseReleaseEvent(QMouseEvent *e) = 0;
		virtual void	reset() = 0;
		virtual void	setViewportSize(int w, int h) = 0;
		virtual void	wheelEvent(QWheelEvent *e) = 0;

	protected:

		QMatrix4x4	MVPMatrix;

};

#endif // GLCAMERA_H
