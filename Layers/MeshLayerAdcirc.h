#ifndef MESHLAYERADCIRC_H
#define MESHLAYERADCIRC_H

#include <QObject>
#include <QKeyEvent>

#include "Adcirc/Fort14.h"
#include "Adcirc/Fort63.h"
#include "Layers/MeshLayer.h"

class MeshLayerAdcirc : public QObject, public MeshLayer
{
		Q_OBJECT
	public:
		explicit MeshLayerAdcirc(QObject *parent = 0);

		Fort14	*getFort14();

		void	setFort14(Fort14 *fort14);
		void	setFort63(Fort63 *fort63);

		virtual void	keyPressEvent(QKeyEvent *e);

	private:

		Fort14	*fort14;
		Fort63	*fort63;

	signals:

		void	updateGL();

	public slots:

		void	timestepLoaded(Fort63* fort63, int ts);

};

#endif // MESHLAYERADCIRC_H
