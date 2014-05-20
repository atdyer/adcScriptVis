#ifndef OPENGLWIDGET_H
#define OPENGLWIDGET_H

#include <GL/glew.h>
#include <GL/glut.h>
#include <QGLWidget>
#include <QtDebug>

class OpenGLWidget : public QGLWidget
{
		Q_OBJECT
	public:
		explicit OpenGLWidget(QWidget *parent = 0);

		void	initializeGL();
		void	resizeGL(int w, int h);
		void	paintGL();

	signals:

	public slots:

};

#endif // OPENGLWIDGET_H
