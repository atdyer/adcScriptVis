#ifndef GLCAMERA3D_H
#define GLCAMERA3D_H

#include <QObject>
#include <QtMath>
#include <math.h>

#include "OpenGL/OpenGLData.h"
#include "OpenGL/Cameras/GLCamera.h"

class GLCamera3D : public QObject, public GLCamera
{
		Q_OBJECT
	public:
		explicit GLCamera3D(QObject *parent = 0);

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
		float	dx;
		float	dy;
		int	newX;
		int	newY;
		int	oldX;
		int	oldY;
		float	panX;
		float	panY;
		float	panZ;
		float	xRot;
		float	zRot;
		float	zoom;
		float	zoomScale;

	public slots:

		void	panCamera(float dx, float dy);
		void	rotateCamera(float degrees);
		void	tiltCamera(float degrees);
		void	zoomCamera(int direction, float scale);

};

#endif // GLCAMERA3D_H
