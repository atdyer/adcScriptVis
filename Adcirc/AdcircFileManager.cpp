#include "AdcircFileManager.h"

AdcircFileManager::AdcircFileManager(QObject *parent) :
	QObject(parent)
{
	progressBar = 0;
	testLayer = 0;
}


AdcircFileManager::~AdcircFileManager()
{
	workerThread.quit();
	workerThread.wait();
}


void AdcircFileManager::openFile(QFileInfo info)
{
	if (info.suffix() == QString("14"))
	{
		openFort14(info.absoluteFilePath());
	}
	else if (info.suffix() == QString("63"))
	{
		openFort63(info.absoluteFilePath());
	}
}


void AdcircFileManager::setProgressBar(QProgressBar *progressBar)
{
	this->progressBar = progressBar;
}


void AdcircFileManager::openFort14(QString fileLocation)
{
	Fort14 *fort14 = new Fort14(this);
	Fort14IO *reader = new Fort14IO(fort14, fileLocation);

	if (progressBar)
	{
		connect(reader, SIGNAL(progressStartValue(int)), progressBar, SLOT(setMinimum(int)));
		connect(reader, SIGNAL(progressEndValue(int)), progressBar, SLOT(setMaximum(int)));
		connect(reader, SIGNAL(readingInProgress(bool)), progressBar, SLOT(setVisible(bool)));
		connect(reader, SIGNAL(progress(int)), progressBar, SLOT(setValue(int)));
	}
	connect(reader, SIGNAL(fort14Loaded(Fort14*)), this, SLOT(fort14Loaded(Fort14*)));

	QThreadPool::globalInstance()->start(reader);
}


void AdcircFileManager::openFort63(QString fileLocation)
{
	Fort63 *fort63 = new Fort63(this);
	Fort63IO *reader = new Fort63IO(fort63, fileLocation);
	fort63->setReader(reader);

	reader->moveToThread(&workerThread);
	if (progressBar)
	{
		connect(reader, SIGNAL(progressStartValue(int)), progressBar, SLOT(setMinimum(int)));
		connect(reader, SIGNAL(progressEndValue(int)), progressBar, SLOT(setMaximum(int)));
		connect(reader, SIGNAL(readingInProgress(bool)), progressBar, SLOT(setVisible(bool)));
		connect(reader, SIGNAL(progress(int)), progressBar, SLOT(setValue(int)));
	}
	connect(reader, SIGNAL(fort63Loaded(Fort63*)), this, SLOT(fort63Loaded(Fort63*)));
	connect(&workerThread, SIGNAL(finished()), reader, SLOT(deleteLater()));

	if (!workerThread.isRunning())
		workerThread.start();

	QMetaObject::invokeMethod(reader, "initialize");
}


void AdcircFileManager::fort14Loaded(Fort14 *fort14)
{
	/* This would be where we add a new MeshLayerAdcirc
	 * to the set that this object is managing */
	testLayer = new MeshLayerAdcirc(this);
	testLayer->setFort14(fort14);

	emit meshLayerLoaded(testLayer);
}


void AdcircFileManager::fort63Loaded(Fort63 *fort63)
{
	/* This would be a good spot to ask the user
	 * which fort.14 file to associate this data
	 * with. */
	if (testLayer)
		testLayer->setFort63(fort63);
}
