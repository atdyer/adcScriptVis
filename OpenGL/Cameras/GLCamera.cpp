#include "GLCamera.h"

GLCamera::GLCamera(QObject *parent) :
	QObject(parent)
{
	ModelViewMatrix.setToIdentity();
	ProjectionMatrix.setToIdentity();
}


const float *GLCamera::getMVP()
{
	return (ProjectionMatrix*ModelViewMatrix).data();
}
