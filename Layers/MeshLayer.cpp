#include "MeshLayer.h"

MeshLayer::MeshLayer(QObject *parent) :
	QObject(parent),
	Layer()
{
	glLoaded = false;
	numVertices = 0;
	numIndices = 0;

	outlineShader = 0;
	fillShader = 0;

	VAOId = 0;
	VBOId = 0;
	IBOId = 0;

	initializeGL();
}


MeshLayer::~MeshLayer()
{
	if (VAOId)
		glDeleteBuffers(1, &VAOId);
	if (VBOId)
		glDeleteBuffers(1, &VBOId);
	if (IBOId)
		glDeleteBuffers(1, &IBOId);
}


void MeshLayer::render()
{
	if (glLoaded && numVertices && numIndices)
	{
		glBindVertexArray(VAOId);

		if (fillShader)
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			if (fillShader->use())
			{
				glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_INT, (GLvoid*)0);
			}
		}

		if (outlineShader)
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			if (outlineShader->use())
			{
				glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_INT, (GLvoid*)0);
			}
		}

	}
}


void MeshLayer::setCamera(GLCamera *newCamera)
{
	camera = newCamera;
	if (outlineShader)
		outlineShader->setCamera(camera);
	if (fillShader)
		fillShader->setCamera(camera);
}


void MeshLayer::setFillShader(GLShader *newFillShader)
{
	fillShader = newFillShader;
}


void MeshLayer::setIndices(QVector<Element> *elements)
{
	if (glLoaded)
	{
		numIndices = 3*elements->size();
		const size_t indexBufferSize = sizeof(GLuint)*numIndices;

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBOId);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexBufferSize, NULL, GL_STATIC_DRAW);

		GLuint *glElementData = (GLuint *)glMapBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_WRITE_ONLY);
		if (glElementData)
		{
			for (int i=0; i<elements->size(); ++i)
			{
				glElementData[3*i+0] = (GLuint)elements->at(i).n1-1;
				glElementData[3*i+1] = (GLuint)elements->at(i).n2-1;
				glElementData[3*i+2] = (GLuint)elements->at(i).n3-1;
			}
		} else {
			numIndices = 0;
			qDebug() << "Mesh Layer: Unable to map index buffer";
		}

		glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	} else {
		qDebug() << "Mesh Layer: Unable to set elements, GL not initialized";
	}
}


void MeshLayer::setIndices(QVector<int> *indices)
{
	if (glLoaded)
	{
		numIndices = indices->size();
		const size_t indexBufferSize = sizeof(GLuint)*numIndices;

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBOId);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexBufferSize, NULL, GL_STATIC_DRAW);

		GLuint *glElementData = (GLuint *)glMapBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_WRITE_ONLY);
		if (glElementData)
		{
			for (int i=0; i<indices->size(); ++i)
			{
				glElementData[i] = indices->at(i);
			}
		} else {
			numIndices = 0;
			qDebug() << "Mesh Layer: Unable to map index buffer";
		}

		glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	} else {
		qDebug() << "Mesh Layer: Unable to set indices, GL not initialized";
	}
}


void MeshLayer::setOutlineShader(GLShader *newOutlineShader)
{
	outlineShader = newOutlineShader;
}


void MeshLayer::setVertices(QVector<Node> *nodes)
{
	if (glLoaded)
	{
		numVertices = nodes->size();
		const size_t vertexBufferSize = 4*sizeof(GLfloat)*numVertices;

		glBindBuffer(GL_ARRAY_BUFFER, VBOId);
		glBufferData(GL_ARRAY_BUFFER, vertexBufferSize, NULL, GL_STATIC_DRAW);

		GLfloat *glVertexData = (GLfloat *)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
		if (glVertexData)
		{
			for (int i=0; i<nodes->size(); ++i)
			{
				glVertexData[4*i+0] = (GLfloat)nodes->at(i).x;
				glVertexData[4*i+1] = (GLfloat)nodes->at(i).y;
				glVertexData[4*i+2] = (GLfloat)nodes->at(i).z;
				glVertexData[4*i+3] = (GLfloat)1.0;
			}
		} else {
			numVertices = 0;
			qDebug() << "Mesh Layer: Unable to map vertex buffer";
		}

		glUnmapBuffer(GL_ARRAY_BUFFER);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	} else {
		qDebug() << "Mesh Layer: Unable to set nodes, GL not initialized";
	}
}


void MeshLayer::setVertices(QVector<float> *vertices)
{
	if (glLoaded)
	{
		numVertices = vertices->size() / 4;
		const size_t vertexBufferSize = sizeof(GLfloat)*vertices->size();

		glBindBuffer(GL_ARRAY_BUFFER, VBOId);
		glBufferData(GL_ARRAY_BUFFER, vertexBufferSize, NULL, GL_STATIC_DRAW);

		GLfloat *glVertexData = (GLfloat *)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
		if (glVertexData)
		{
			for (int i=0; i<vertices->size(); ++i)
			{
				glVertexData[i] = (GLfloat)vertices->at(i);
			}
		} else {
			numVertices = 0;
			qDebug() << "Mesh Layer: Unable to map vertex buffer";
		}

		glUnmapBuffer(GL_ARRAY_BUFFER);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	} else {
		qDebug() << "Mesh Layer: Unable to set vertices, GL not initialized";
	}
}


void MeshLayer::initializeGL()
{
	glGenVertexArrays(1, &VAOId);
	glGenBuffers(1, &VBOId);
	glGenBuffers(1, &IBOId);

	glBindVertexArray(VAOId);

	glBindBuffer(GL_ARRAY_BUFFER, VBOId);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4*sizeof(GLfloat), 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBOId);

	glBindVertexArray(0);

	glLoaded = true;
}
