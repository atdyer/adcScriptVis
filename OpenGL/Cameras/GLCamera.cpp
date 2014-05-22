#include "GLCamera.h"

GLCamera::GLCamera()
{
	MVPMatrix.setToIdentity();
}


const float *GLCamera::getMVP()
{
	return MVPMatrix.data();
}
