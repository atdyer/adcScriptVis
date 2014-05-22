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
	glDisable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glPointSize(10);
	glEnable(GL_POINT_SMOOTH);
//	glEnable(GL_LINE_SMOOTH);

//	InitializeTestMesh();
}


void OpenGLWidget::resizeGL(int w, int h)
{
	glViewport(0, 0, w, h);
	if (currentLayerStack)
		currentLayerStack->setViewportSize(w, h);
}


void OpenGLWidget::paintGL()
{
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


void OpenGLWidget::InitializeTestMesh()
{
	currentLayerStack = new LayerStack(this);
	MeshLayer *testMesh = new MeshLayer();

	QVector<float> vertices;
	QVector<int> indices;

	vertices.append(-.5);
	vertices.append(-.5);
	vertices.append(0.0);
	vertices.append(1.0);
	vertices.append(.5);
	vertices.append(-.5);
	vertices.append(0.0);
	vertices.append(1.0);
	vertices.append(0.0);
	vertices.append(.5);
	vertices.append(0.0);
	vertices.append(1.0);

	indices.append(0);
	indices.append(1);
	indices.append(2);

	testMesh->setVertices(&vertices);
	testMesh->setIndices(&indices);

	SolidShader *testShader = new SolidShader(this);
	SolidShader *testShader2 = new SolidShader(this);
	testShader->setColor(QColor(Qt::blue).lighter());
	testShader2->setColor(QColor(Qt::red));

	testMesh->setOutlineShader(testShader2);
	testMesh->setFillShader(testShader);

	currentLayerStack->appendLayer(testMesh);

	connect(currentLayerStack, SIGNAL(updateGL()), this, SLOT(updateGL()));

}
