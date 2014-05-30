#ifndef MESHLAYER_H
#define MESHLAYER_H

#include <QObject>
#include <QList>

#include "Adcirc/Data/AdcircData.h"
#include "Layers/Layer.h"
#include "OpenGL/OpenGLData.h"
#include "OpenGL/Cameras/GLCamera.h"
#include "OpenGL/Shaders/GLShader.h"

class MeshLayer : public QObject, public Layer
{
		Q_OBJECT
	public:
		explicit MeshLayer(QObject *parent = 0);
		~MeshLayer();

		virtual void	render();

		void		appendShader(GLShader *shader, GLenum type);
		virtual void	setCamera(GLCamera *newCamera);
		void		setIndices(QVector<Element> *elements);
		void		setIndices(QVector<int> *indices);
		void		setVertices(QVector<Node> *nodes);
		void		setVertices(QVector<float> *vertices);


	private:

		struct ShaderPackage {
				ShaderPackage(GLShader *shader, GLenum type) :
					shader(shader), type(type) {}
				GLShader *shader;
				GLenum type;
		};

		bool	glLoaded;
		int	numVertices;
		int	numIndices;

		QList<ShaderPackage>	shaders;

		GLuint	VAOId;
		GLuint	VBOId;
		GLuint	IBOId;


		void	initializeGL();


};

#endif // MESHLAYER_H
