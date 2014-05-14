#include "OpenGLWidget.h"

OpenGLWidget::OpenGLWidget(QWidget *parent) :
	QGLWidget(parent)
{
}


void OpenGLWidget::initializeGL()
{
	glewExperimental = GL_TRUE;
	GLenum err = glewInit();

	if (err != GLEW_OK)
	{
		qDebug() << "Error: GLEW unable to load OpenGL Extensions";
	} else {
		qDebug() << "OpenGL Extensions Loaded";
	}

	glClearColor(0.1, 0.1, 0.1, 1.0);
	glDisable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glPointSize(10);
	glEnable(GL_POINT_SMOOTH);
	glEnable(GL_LINE_SMOOTH);
}


void OpenGLWidget::resizeGL(int w, int h)
{
	glViewport(0, 0, w, h);
}


void OpenGLWidget::paintGL()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
