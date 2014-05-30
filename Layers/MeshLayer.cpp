#include "MeshLayer.h"

MeshLayer::MeshLayer() :
	Layer()
{
	glLoaded = false;
	glIndicesInitialized = false;
	glVerticesInitialized = false;
	numVertices = 0;
	numIndices = 0;

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
	if (glLoaded && numVertices && numIndices && shaders.size() > 0)
	{
		glBindVertexArray(VAOId);

		for (int i=0; i<shaders.size(); ++i)
		{
			glPolygonMode(GL_FRONT_AND_BACK, shaders[i].type);
			if (shaders[i].shader->use())
			{
				glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_INT, (GLvoid*)0);
			}
		}

	}
}


void MeshLayer::appendShader(GLShader *shader, GLenum type)
{
	if (shader)
	{
		if (camera)
			shader->setCamera(camera);
		shaders.append(ShaderPackage(shader, type));
	}
}


void MeshLayer::setCamera(GLCamera *newCamera)
{
	camera = newCamera;
	for (int i=0; i<shaders.size(); ++i)
		shaders[i].shader->setCamera(camera);
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

		glIndicesInitialized = true;

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

		glIndicesInitialized = true;

	} else {
		qDebug() << "Mesh Layer: Unable to set indices, GL not initialized";
	}
}


void MeshLayer::setVertices(QVector<Node> *nodes)
{
	if (glLoaded)
	{
		numVertices = nodes->size();
		const size_t vertexBufferSize = 8*sizeof(GLfloat)*numVertices;

		glBindBuffer(GL_ARRAY_BUFFER, VBOId);
		glBufferData(GL_ARRAY_BUFFER, vertexBufferSize, NULL, GL_STATIC_DRAW);

		GLfloat *glVertexData = (GLfloat *)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
		if (glVertexData)
		{
			for (int i=0; i<nodes->size(); ++i)
			{
				glVertexData[8*i+0] = (GLfloat)nodes->at(i).x;
				glVertexData[8*i+1] = (GLfloat)nodes->at(i).y;
				glVertexData[8*i+2] = (GLfloat)nodes->at(i).z;
				glVertexData[8*i+3] = (GLfloat)1.0;
				glVertexData[8*i+4] = (GLfloat)0.0;
				glVertexData[8*i+5] = (GLfloat)0.0;
				glVertexData[8*i+6] = (GLfloat)0.0;
				glVertexData[8*i+7] = (GLfloat)1.0;

			}
		} else {
			numVertices = 0;
			qDebug() << "Mesh Layer: Unable to map vertex buffer";
		}

		glUnmapBuffer(GL_ARRAY_BUFFER);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glVerticesInitialized = true;
	} else {
		qDebug() << "Mesh Layer: Unable to set nodes, GL not initialized";
	}
}


void MeshLayer::setVertices(QVector<float> *vertices)
{
	if (glLoaded)
	{
		numVertices = vertices->size() / 8;
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

		glVerticesInitialized = true;
	} else {
		qDebug() << "Mesh Layer: Unable to set vertices, GL not initialized";
	}
}


void MeshLayer::setVertices(QVector<float> *vertices, int offset)
{
	if (glLoaded && glVerticesInitialized)
	{
		offset = offset % 8;
		glBindBuffer(GL_ARRAY_BUFFER, VBOId);
		GLfloat *glVertexData = (GLfloat *)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
		if (glVertexData)
		{
			for (int i=0; i<numVertices; ++i)
			{
				glVertexData[8*i+offset] = (GLfloat)vertices->at(i);
			}
		} else {
			qDebug() << "Mesh Layer: Unable to map vertex buffer";
		}

		glUnmapBuffer(GL_ARRAY_BUFFER);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	} else {
		qDebug() << "Mesh Layer: Unable to set vertex values, GL not initialized";
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
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 8*sizeof(GLfloat), 0);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 8*sizeof(GLfloat), (GLvoid*)(4*sizeof(GLfloat)));

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBOId);

	glBindVertexArray(0);

	glLoaded = true;
}
