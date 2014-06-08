#include "GradientShader.h"

bool StopIsLessThan(const QGradientStop &stop1, const QGradientStop &stop2)
{
	return stop1.first < stop2.first;
}

GradientShader::GradientShader(bool useWaterElevations, QObject *parent) :
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
			       "uniform int stopCount;"
			       "uniform float values[10];"
			       "uniform vec4 colors[10];"
			       "void main(void)"
			       "{"
			       "	ex_Color = colors[0];"
			       "	for (int i=1; i<stopCount; ++i)"
			       "	{"
			       "		float t = clamp((in_Position.z - values[i-1]) / (values[i]-values[i-1]), 0.0, 1.0);"
			       "		ex_Color = mix(ex_Color, colors[i], t*t*(3.0 - 2.0*t));"
			       "	}"
			       "	gl_Position = MVPMatrix*(in_Position*vec4(1.0, 1.0, 0.1, 1.0));"
			       "}";
	} else {
		vertexSource = "#version 110"
			       "\n"
			       "attribute vec4 in_Position;"
			       "attribute vec4 water_Properties;"
			       "varying vec4 ex_Color;"
			       "uniform mat4 MVPMatrix;"
			       "uniform int stopCount;"
			       "uniform float values[10];"
			       "uniform vec4 colors[10];"
			       "void main(void)"
			       "{"
			       "	ex_Color = colors[0];"
			       "	vec4 waterPosition = vec4(in_Position.x, in_Position.y, water_Properties.z, in_Position.w);"
			       "	if (water_Properties.z == -99999.0)"
			       "	{"
				"		ex_Color = vec4(0.0, 0.0, 0.0, 0.0);"
				"	} else {"
			       "		for (int i=1; i<stopCount; ++i)"
			       "		{"
			       "			float t = clamp((water_Properties.z - values[i-1]) / (values[i]-values[i-1]), 0.0, 1.0);"
			       "			ex_Color = mix(ex_Color, colors[i], t*t*(3.0 - 2.0*t));"
			       "		}"
				"	}"
			       "	gl_Position = MVPMatrix*(waterPosition);"
			       "}";
	}

	fragmentSource = "#version 110"
			 "\n"
			 "varying vec4 ex_Color;"
			 "void main(void)"
			 "{"
			 "	gl_FragColor = ex_Color;"
			 "}";

	lowValue = 0.0;
	highValue = 1.0;

	compileShader();
	updateUniforms();
}


void GradientShader::setGradientStops(const QGradientStops &newStops)
{
	gradientStops = newStops;
	updateUniforms();
}


void GradientShader::setGradientRange(float newLow, float newHigh)
{
	lowValue = newLow;
	highValue = newHigh;
	updateUniforms();
}


void GradientShader::compileShader()
{
	const char* fullVertSource = vertexSource.data();
	const char* fullFragSource = fragmentSource.data();

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


void GradientShader::updateUniforms()
{
	if (loaded && camSet)
	{
		glUseProgram(programID);

		GLint MVPUniform = glGetUniformLocation(programID, "MVPMatrix");
		GLint StopCountUniform = glGetUniformLocation(programID, "stopCount");
		GLint ValuesUniform = glGetUniformLocation(programID, "values");
		GLint ColorsUniform = glGetUniformLocation(programID, "colors");

		GLint stopCount = gradientStops.size();

		if (stopCount > 1)
		{

			qSort(gradientStops.begin(), gradientStops.end(), StopIsLessThan);
			GLfloat stopValues[stopCount];
			GLfloat colorValues[stopCount*4];
			for (int i=0; i<gradientStops.size(); ++i)
			{
				stopValues[i] = getValueFromStop(gradientStops[i].first);
				colorValues[4*i+0] = gradientStops[i].second.red() / 255.0;
				colorValues[4*i+1] = gradientStops[i].second.green() / 255.0;
				colorValues[4*i+2] = gradientStops[i].second.blue() / 255.0;
				colorValues[4*i+3] = gradientStops[i].second.alpha() / 255.0;
			}

			glUniformMatrix4fv(MVPUniform, 1, GL_FALSE, camera->getMVP());
			glUniform1i(StopCountUniform, stopCount);
			glUniform1fv(ValuesUniform, stopCount, stopValues);
			glUniform4fv(ColorsUniform, stopCount, colorValues);
		}
			uniformsSet = true;

	} else {
		uniformsSet = false;
	}
}


float GradientShader::getValueFromStop(float stop)
{
	return lowValue + ((1.0-stop) * (highValue - lowValue));
}
