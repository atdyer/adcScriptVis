#ifndef GLCAMERA_H
#define GLCAMERA_H

#include <QObject>
#include <QMatrix4x4>
#include <QMouseEvent>
#include <QWheelEvent>

class GLCamera : public QObject
{
		Q_OBJECT
	public:
		explicit GLCamera(QObject *parent = 0);

		const float	*getMVP();

		virtual void	mouseMoveEvent(QMouseEvent *e) = 0;
		virtual void	wheelEvent(QWheelEvent *e) = 0;

	protected:

		QMatrix4x4	ModelViewMatrix;
		QMatrix4x4	ProjectionMatrix;

	signals:

	public slots:

};

#endif // GLCAMERA_H
