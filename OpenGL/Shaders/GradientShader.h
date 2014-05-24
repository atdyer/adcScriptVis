#ifndef GRADIENTSHADER_H
#define GRADIENTSHADER_H

#include <QObject>
#include <QGradient>

#include "OpenGL/Shaders/GLShader.h"

class GradientShader : public QObject, public GLShader
{
		Q_OBJECT
	public:
		explicit GradientShader(QObject *parent = 0);

		void		setGradientStops(const QGradientStops &newStops);
		void		setGradientRange(float newLow, float newHigh);

	protected:

		std::string	vertexSource;
		std::string	fragmentSource;

		QGradientStops	gradientStops;
		float		lowValue;
		float		highValue;

		virtual void	compileShader();
		virtual void	updateUniforms();

	private:

		float		getValueFromStop(float stop);

};

#endif // GRADIENTSHADER_H
