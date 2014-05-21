#ifndef GLCAMERA2D_H
#define GLCAMERA2D_H

#include <QObject>
#include "OpenGL/Cameras/GLCamera.h"

class GLCamera2D : public GLCamera
{
	public:
		GLCamera2D(QObject *parent = 0);

		virtual void	mouseMoveEvent(QMouseEvent *e);
		virtual void	wheelEvent(QWheelEvent *e);


};

#endif // GLCAMERA2D_H
