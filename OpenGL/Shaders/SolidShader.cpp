#include "SolidShader.h"

SolidShader::SolidShader(QObject *parent) :
	QObject(parent),
	GLShader()
{
	vertexSource = "#version 110"
			"\n"
			"attribute vec4 in_Position;"
			"varying vec4 ex_Color;"
			"uniform mat4 MVPMatrix;"
			"uniform vec4 ColorVector;"
			"void main(void)"
			"{"
			"       gl_Position = MVPMatrix*(in_Position*vec4(1.0, 1.0, 0.1, 1.0));"
			"       ex_Color = ColorVector;"
			"}";

	fragmentSource = "#version 110"
			"\n"
			"varying vec4 ex_Color;"
			"void main(void)"
			"{"
			"	gl_FragColor = ex_Color;"
			"}";

	color = QColor(1.0, 1.0, 1.0, 1.0);

	compileShader();
	updateUniforms();
}


void SolidShader::setColor(QColor newColor)
{
	color = newColor;
	updateUniforms();
}


void SolidShader::compileShader()
{
	const char *fullVertSource = vertexSource.data();
	const char *fullFragSource = fragmentSource.data();

	GLuint vertexShaderID = compileShaderPart(fullVertSource, GL_VERTEX_SHADER);
	GLuint fragmentShaderID = compileShaderPart(fullFragSource, GL_FRAGMENT_SHADER);

	if (vertexShaderID && fragmentShaderID)
	{
		programID = glCreateProgram();
		glBindAttribLocation(programID, 0, "in_Position");
		glAttachShader(programID, vertexShaderID);
		glAttachShader(programID, fragmentShaderID);
		glLinkProgram(programID);
		glDeleteShader(vertexShaderID);
		glDeleteShader(fragmentShaderID);
		loaded = true;
	}
}


void SolidShader::updateUniforms()
{
	if (loaded && camSet)
	{
		glUseProgram(programID);

		GLint MVPUniform = glGetUniformLocation(programID, "MVPMatrix");
		GLint ColorUniform = glGetUniformLocation(programID, "ColorVector");

		GLfloat currColor[4] = {color.red() / 255.0f,
					color.green() / 255.0f,
					color.blue() / 255.0f,
					color.alpha() / 255.0f};

		glUniformMatrix4fv(MVPUniform, 1, GL_FALSE, camera->getMVP());
		glUniform4fv(ColorUniform, 1, currColor);

		uniformsSet = true;

	} else {
		uniformsSet = false;
	}
}

