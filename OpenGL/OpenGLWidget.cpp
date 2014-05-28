#include "OpenGLWidget.h"

OpenGLWidget::OpenGLWidget(QWidget *parent) :
	QGLWidget(parent)
{
	currentLayerStack = 0;
	setMouseTracking(false);
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

	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);
	glDepthFunc(GL_LEQUAL);
	glDepthRange(0.0f, 1.0f);
	glEnable(GL_POLYGON_OFFSET_FILL);
	glPolygonOffset(1.0, 1.0);

	glEnable(GL_BLEND);
	glEnable(GL_ALPHA_TEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glPointSize(10);
//	glEnable(GL_POINT_SMOOTH);
//	glEnable(GL_LINE_SMOOTH);

}


void OpenGLWidget::resizeGL(int w, int h)
{
	glViewport(0, 0, w, h);
	if (currentLayerStack)
		currentLayerStack->setViewportSize(w, h);
}


void OpenGLWidget::paintGL()
{
	glClearDepth(1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	if (currentLayerStack)
		currentLayerStack->render();
}


void OpenGLWidget::setCurrentLayerStack(LayerStack *newStack)
{
	if (currentLayerStack)
		disconnect(currentLayerStack, 0, this, 0);

	currentLayerStack = newStack;
	currentLayerStack->setViewportSize(geometry().width(), geometry().height());
	connect(currentLayerStack, SIGNAL(updateGL()), this, SLOT(updateGL()));

	updateGL();
}


void OpenGLWidget::mouseMoveEvent(QMouseEvent *e)
{
	if (currentLayerStack)
		currentLayerStack->mouseMoveEvent(e);
}


void OpenGLWidget::mousePressEvent(QMouseEvent *e)
{
	if (currentLayerStack)
		currentLayerStack->mousePressEvent(e);
}


void OpenGLWidget::mouseReleaseEvent(QMouseEvent *e)
{
	if (currentLayerStack)
		currentLayerStack->mouseReleaseEvent(e);
}


void OpenGLWidget::wheelEvent(QWheelEvent *e)
{
	if (currentLayerStack)
		currentLayerStack->wheelEvent(e);
}


void OpenGLWidget::reset()
{
	if (currentLayerStack)
		currentLayerStack->resetCamera();
}


void OpenGLWidget::use2DCamera()
{
	if (currentLayerStack)
		currentLayerStack->use2DCamera();
}


void OpenGLWidget::use3DCamera()
{
	if (currentLayerStack)
		currentLayerStack->use3DCamera();
}
