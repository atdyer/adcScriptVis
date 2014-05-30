#ifndef SOLIDSHADER_H
#define SOLIDSHADER_H

#include <QObject>
#include <QColor>

#include "OpenGL/Shaders/GLShader.h"

class SolidShader : public QObject, public GLShader
{
		Q_OBJECT
	public:
		explicit SolidShader(bool useWaterElevations, QObject *parent = 0);

		void	getColor(QColor newColor);
		void	setColor(QColor newColor);

	protected:

		std::string	vertexSource;
		std::string	fragmentSource;

		QColor	color;

		virtual void	compileShader();
		virtual void	updateUniforms();
};

#endif // SOLIDSHADER_H
