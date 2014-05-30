#ifndef ADCIRCFILEMANAGER_H
#define ADCIRCFILEMANAGER_H

#include <QObject>
#include <QFileInfo>
#include <QThread>
#include <QThreadPool>

#include "Adcirc/Fort14.h"
#include "Adcirc/Fort63.h"
#include "Adcirc/IO/Fort14IO.h"
#include "Adcirc/IO/Fort63IO.h"
#include "Layers/MeshLayerAdcirc.h"

class AdcircFileManager : public QObject
{
		Q_OBJECT
	public:
		explicit AdcircFileManager(QObject *parent = 0);
		~AdcircFileManager();

		void	openFile(QFileInfo info);
		void	setProgressBar(QProgressBar *progressBar);

	private:

		QProgressBar	*progressBar;
		QThread		workerThread;

		MeshLayerAdcirc	*testLayer;

		void	openFort14(QString fileLocation);
		void	openFort63(QString fileLocation);

	signals:

		void	meshLayerLoaded(MeshLayerAdcirc *meshLayer);

	public slots:

		void	fort14Loaded(Fort14 *fort14);
		void	fort63Loaded(Fort63 *fort63);

};

#endif // ADCIRCFILEMANAGER_H
