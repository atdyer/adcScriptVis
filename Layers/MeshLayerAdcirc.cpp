#include "MeshLayerAdcirc.h"

MeshLayerAdcirc::MeshLayerAdcirc(QObject *parent) :
	QObject(parent),
	MeshLayer()
{
	fort14 = 0;
	fort63 = 0;
}


Fort14 *MeshLayerAdcirc::getFort14()
{
	return fort14;
}


void MeshLayerAdcirc::setFort14(Fort14 *fort14)
{
	if (fort14)
	{
		setVertices(fort14->getNodes());
		setIndices(fort14->getElements());
		this->fort14 = fort14;
	}
}


void MeshLayerAdcirc::setFort63(Fort63 *fort63)
{
	if (fort63)
	{
		connect(fort63, SIGNAL(timestepLoaded(Fort63*,int)), this, SLOT(timestepLoaded(Fort63*,int)));
		this->fort63 = fort63;
		setVertices(fort63->getElevations(), 6);
	}
}


void MeshLayerAdcirc::timestepLoaded(Fort63 *fort63, int ts)
{
	if (fort63)
	{
		qDebug() << "Timestep loaded: " << ts;
		setVertices(fort63->getElevations(), 6);
		emit updateGL();
	}
}


void MeshLayerAdcirc::keyPressEvent(QKeyEvent *e)
{
	if (e->key() == Qt::Key_Right)
	{
		if (fort63)
			fort63->loadTimestep(fort63->getCurrentTimestep()+1);
	}
	else if (e->key() == Qt::Key_Left)
	{
		if (fort63)
			fort63->loadTimestep(fort63->getCurrentTimestep()-1);
	}
}
