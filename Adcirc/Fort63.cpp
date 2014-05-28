#include "Fort63.h"

Fort63::Fort63(QObject *parent) :
	QObject(parent)
{

}


Fort63::~Fort63()
{
	workerThread.quit();
	workerThread.wait();
}


void Fort63::setPath(QString fileLocation, QProgressBar *progressBar)
{
	Fort63IO *io = new Fort63IO(this, fileLocation);

	// Move to worker thread
	io->moveToThread(&workerThread);

	// Make connections
	connect(&workerThread, SIGNAL(started()), io, SLOT(initialize()));
	connect(&workerThread, SIGNAL(finished()), io, SLOT(deleteLater()));
	connect(io, SIGNAL(timestepFinishedReading(int)), this, SLOT(timestepFinishedReading(int)));
	if (progressBar)
	{
		connect(io, SIGNAL(progressStartValue(int)), progressBar, SLOT(setMinimum(int)));
		connect(io, SIGNAL(progressEndValue(int)), progressBar, SLOT(setMaximum(int)));
		connect(io, SIGNAL(readingInProgress(bool)), progressBar, SLOT(setVisible(bool)));
		connect(io, SIGNAL(progess(int)), progressBar, SLOT(setValue(int)));
		connect(io, SIGNAL(fort63Loaded(Fort63*)), this, SIGNAL(initialized(Fort63*)));
	}

	// Start the thread
	workerThread.start();

}


void Fort63::timestepFinishedReading(int ts)
{
	emit timestepLoaded(ts);
}
