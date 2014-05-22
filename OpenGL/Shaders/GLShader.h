#ifndef GLSHADER_H
#define GLSHADER_H

#include <QDebug>

#include "OpenGL/OpenGLData.h"
#include "OpenGL/Cameras/GLCamera.h"

class GLShader
{
	public:
		explicit GLShader();
		~GLShader();

		bool	use();
		void	setCamera(GLCamera *newCamera);

	protected:

		GLuint		programID;
		GLCamera	*camera;
		bool		camSet;
		bool		loaded;
		bool		uniformsSet;

		virtual void	updateCameraUniform();
		GLuint		compileShaderPart(const char *source, GLenum shaderType);
		virtual void	compileShader() = 0;
		virtual void	updateUniforms() = 0;

};

#endif // GLSHADER_H
