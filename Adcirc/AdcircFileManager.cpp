#include "AdcircFileManager.h"

AdcircFileManager::AdcircFileManager(QObject *parent) :
	QObject(parent)
{
	progressBar = 0;
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
	connect(reader, SIGNAL(fort14Loaded(Fort14*)), this, SIGNAL(fort14Loaded(Fort14*)));

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
		connect(reader, SIGNAL(progess(int)), progressBar, SLOT(setValue(int)));
	}
	connect(reader, SIGNAL(fort63Loaded(Fort63*,int)), this, SIGNAL(fort63Loaded(Fort63*,int)));

	if (!workerThread.isRunning())
		workerThread.start();

	QMetaObject::invokeMethod(reader, "initialize");
}
