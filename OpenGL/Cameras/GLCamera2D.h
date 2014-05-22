#ifndef GLCAMERA2D_H
#define GLCAMERA2D_H

#include <QObject>

#include "OpenGL/OpenGLData.h"
#include "OpenGL/Cameras/GLCamera.h"

class GLCamera2D : public QObject, public GLCamera
{
		Q_OBJECT
	public:
		explicit GLCamera2D(QObject *parent = 0);

		virtual const float	*getMVP();

		virtual void	mouseMoveEvent(QMouseEvent *e);
		virtual void	mousePressEvent(QMouseEvent *e);
		virtual void	mouseReleaseEvent(QMouseEvent *e);
		virtual void	reset();
		virtual void	setViewportSize(int w, int h);
		virtual void	wheelEvent(QWheelEvent *e);

	private:

		int	width;
		int	height;
		float	pixelToViewRatio;
		int	dx;
		int	dy;
		int	newX;
		int	newY;
		int	oldX;
		int	oldY;
		float	zoom;
		float	zoomScale;


};

#endif // GLCAMERA2D_H
