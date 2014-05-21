#ifndef GLSHADER_H
#define GLSHADER_H

#include <QObject>
#include <QDebug>
#include "OpenGL/OpenGLData.h"

enum ShaderType {NoShaderType, SolidShaderType, GradientShaderType};

class GLShader : public QObject
{
		Q_OBJECT
	public:
		explicit GLShader(QObject *parent = 0);
		virtual ~GLShader();

		bool	Use();
//		void	SetCamera(GLCamera *newCamera);

		virtual	ShaderType	GetShaderType() = 0;

	protected:

		GLuint		programID;
//		GLCamera	*camera;
		bool		camSet;
		bool		loaded;
		bool		uniformsSet;

		virtual void	UpdateCameraUniform();
		GLuint		CompileShaderPart(const char *source, GLenum shaderType);
		virtual void	CompileShader() = 0;
		virtual void	UpdateUniforms() = 0;

	signals:

	public slots:

};

#endif // GLSHADER_H
