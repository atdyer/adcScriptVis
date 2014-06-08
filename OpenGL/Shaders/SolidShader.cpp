#include "SolidShader.h"

SolidShader::SolidShader(bool useWaterElevations, QObject *parent) :
	QObject(parent),
	GLShader()
{
	if (!useWaterElevations)
	{
		vertexSource = "#version 110"
				"\n"
				"attribute vec4 in_Position;"
				"attribute vec4 water_Properties;"
				"varying vec4 ex_Color;"
				"uniform mat4 MVPMatrix;"
				"uniform vec4 ColorVector;"
				"void main(void)"
				"{"
				"       gl_Position = MVPMatrix*(in_Position*vec4(1.0, 1.0, 0.1, 1.0));"
				"       ex_Color = ColorVector;"
				"}";
	} else {
		vertexSource = "#version 110"
				"\n"
				"attribute vec4 in_Position;"
				"attribute vec4 water_Properties;"
				"varying vec4 ex_Color;"
				"uniform mat4 MVPMatrix;"
				"uniform vec4 ColorVector;"
				"void main(void)"
				"{"
				"	vec4 waterPosition = vec4(in_Position.x, in_Position.y, water_Properties.z, in_Position.w);"
				"       gl_Position = MVPMatrix*(waterPosition*vec4(1.0, 1.0, 0.1, 1.0));"
				"	if (water_Properties.z == -99999.0)"
				"	{"
				"		ex_Color = vec4(1.0, 0.0, 0.0, 1.0);"
				"	} else {"
				"		ex_Color = ColorVector;"
				"	}"
				"}";
	}

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
		glBindAttribLocation(programID, 1, "water_Properties");
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

