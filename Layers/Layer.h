#ifndef LAYER_H
#define LAYER_H

#include <QObject>

#include "OpenGL/Cameras/GLCamera.h"

class Layer : public QObject
{
		Q_OBJECT
	public:
		explicit Layer(QObject *parent = 0);

		virtual void	render() = 0;
		void		setCamera(GLCamera *newCamera);

	protected:

		GLCamera	*camera;

	signals:

	public slots:

};

#endif // LAYER_H
