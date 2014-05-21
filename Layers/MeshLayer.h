#ifndef MESHLAYER_H
#define MESHLAYER_H

#include "Adcirc/Data/AdcircData.h"
#include "Layers/Layer.h"
#include "OpenGL/OpenGLData.h"
#include "OpenGL/Cameras/GLCamera.h"
#include "OpenGL/Shaders/GLShader.h"

class MeshLayer : public Layer
{
	public:
		MeshLayer();
		~MeshLayer();

		virtual void	render();

		void		setIndices(QVector<Element> *elements);
		void		setIndices(QVector<int> *indices);
		void		setVertices(QVector<Node> *nodes);
		void		setVertices(QVector<float> *vertices);


	private:

		bool	glLoaded;
		int	numVertices;
		int	numIndices;

		GLShader	*outlineShader;
		GLShader	*fillShader;

		GLuint	VAOId;
		GLuint	VBOId;
		GLuint	IBOId;


		void	initializeGL();


};

#endif // MESHLAYER_H
