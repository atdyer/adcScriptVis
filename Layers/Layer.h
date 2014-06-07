#ifndef LAYER_H
#define LAYER_H

#include <QKeyEvent>

#include "OpenGL/Cameras/GLCamera.h"

class Layer
{
	public:
		explicit Layer();

		virtual void	render() = 0;
		virtual void	setCamera(GLCamera *newCamera);

		virtual void	keyPressEvent(QKeyEvent *e);

	protected:

		GLCamera	*camera;

};

#endif // LAYER_H
