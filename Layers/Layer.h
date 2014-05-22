#ifndef LAYER_H
#define LAYER_H

#include "OpenGL/Cameras/GLCamera.h"

class Layer
{
	public:
		explicit Layer();

		virtual void	render() = 0;
		virtual void	setCamera(GLCamera *newCamera);

	protected:

		GLCamera	*camera;

};

#endif // LAYER_H
