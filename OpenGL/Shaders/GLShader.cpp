#include "GLShader.h"

GLShader::GLShader()
{
	programID = 0;
	camera = 0;
	loaded = false;
	camSet = false;
	uniformsSet = false;
}


GLShader::~GLShader()
{
	if (loaded)
	{
		glUseProgram(0);
		glDeleteProgram(programID);
	}
}


bool GLShader::use()
{
	updateCameraUniform();
	if (uniformsSet)
	{
		glUseProgram(programID);
		return true;
	}
	return false;
}


void GLShader::setCamera(GLCamera *newCamera)
{
	if (newCamera)
	{
		camera = newCamera;
		camSet = true;
		updateUniforms();
	}
}


void GLShader::updateCameraUniform()
{
	if (loaded && camSet)
	{
		glUseProgram(programID);
		GLint MVPUniform = glGetUniformLocation(programID, "MVPMatrix");
		glUniformMatrix4fv(MVPUniform, 1, GL_FALSE, camera->getMVP());
	}
}


GLuint GLShader::compileShaderPart(const char *source, GLenum shaderType)
{
	GLuint shaderID = glCreateShader(shaderType);

	if (shaderID != 0)
	{
		glShaderSource(shaderID, 1, &source, NULL);
		glCompileShader(shaderID);

		GLint compileResult;
		glGetShaderiv(shaderID, GL_COMPILE_STATUS, &compileResult);
		if (compileResult != GL_TRUE)
		{
			qDebug() << "Shader Compile Error: " << compileResult;

			GLint logSize;
			glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &logSize);
			char log[logSize];
			glGetShaderInfoLog(shaderID, 250, NULL, log);

			qDebug() << "Shader Log: " << log;

			return 0;
		} else {
			return shaderID;
		}
	} else {
		qDebug() << "Error creating shader";
		return 0;
	}
}
