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

		void	openFort14(QString fileLocation);
		void	openFort63(QString fileLocation);

	signals:

		void	fort14Loaded(Fort14 *fort14);
		void	fort63Loaded(Fort63 *fort63, int ts);

	public slots:

};

#endif // ADCIRCFILEMANAGER_H
