#include "Fort63IO.h"

Fort63IO::Fort63IO(Fort63 *fort63, QString fileLocation) :
	QObject()
{
	this->fort63 = fort63;
	this->file = 0;
	this->fileLoc = fileLocation;
	this->fileInitialized = false;
	this->fileMapped = false;
	this->timestepSize = 0;
}


Fort63IO::~Fort63IO()
{	
}


void Fort63IO::mapFile()
{
	if (file && file->isOpen() && fileInitialized)
	{
		int currProgress = 0;
		int maxProgress = fort63->numNodes + fort63->numDatasets-1;
		int onePercent = 0.01 * maxProgress;
		emit progressStartValue(0);
		emit progressEndValue(maxProgress);
		emit readingInProgress(true);

		// Skip to the position of the first node in the first timestep
		fileStream.readLine();

		// Mark the position of the first timestep
		map[1] = fileStream.pos();

		// Read the first timestep's values
		int node;
		float elevation;
		for (int i=0; i<fort63->numNodes; ++i)
		{
			fileStream >> node;
			fileStream >> elevation;
			fort63->elevations.append(elevation);

			++currProgress;
			if (currProgress % onePercent == 0)
				emit progress(currProgress);
		}
		emit timestepLoaded(fort63, 1);
		fort63->currentTimestep = 1;
		fileStream.readLine();

		// Calculate the timestep's size
		timestepSize = fileStream.pos() - map[1];

		// Read and verify the second timestep's header
		if (verifyHeader(2, fileStream.readLine()))
		{
			// Mark the position of the second timestep
			map[2] = fileStream.pos();
			fileMapped = true;

			// Map the rest of the timesteps
			for (int ts=2; ts<fort63->numDatasets; ++ts)
			{
				// Seek to the correct position
				fileStream.seek(fileStream.pos() + timestepSize);
				if (verifyHeader(ts+1, fileStream.readLine()))
				{
					map[ts+1] = fileStream.pos();
				} else {
					qDebug() << "Mapping error in timestep" << ts;
					fileMapped = false;
					break;
				}

				++currProgress;
				if (currProgress % onePercent == 0)
					emit progress(currProgress);
			}
		}
		emit readingInProgress(false);
	}
}


bool Fort63IO::verifyHeader(int ts, QString header)
{
	QStringList headerValues = header.split(QRegExp("\\s+"), QString::SkipEmptyParts);
	if (headerValues.length() == 2)
	{
		float targetTime = ts * fort63->timestepSeconds * fort63->outputInterval;
		float targetTimestep = ts * fort63->outputInterval;
		bool timeHit = headerValues[0].toFloat() == targetTime;
		bool timestepHit = headerValues[1].toInt() == targetTimestep;
		return timeHit && timestepHit;
	}
	return false;
}


void Fort63IO::initialize()
{

	file = new QFile(fileLoc, this);
	if (!file->open(QIODevice::ReadOnly | QIODevice::Text))
		return;

	fileStream.setDevice(file);

	// Read the header
	fort63->setGridID(fileStream.readLine());
	fileStream >> fort63->numDatasets;
	fileStream >> fort63->numNodes;
	fort63->elevations.reserve(fort63->numNodes);
	float temp;
	fileStream >> temp;
	fileStream >> fort63->outputInterval;
	fort63->timestepSeconds = temp/fort63->outputInterval;
	fileStream.readLine();
	fileInitialized = true;

	mapFile();

	emit fort63Loaded(fort63);
}


void Fort63IO::loadTimestep(int ts)
{
	if (fileMapped && file->isOpen() && ts > 0 && ts < fort63->numDatasets)
	{
		qint64 tsStart = map.value(ts, -1);

		if (tsStart != -1)
		{

			int currProgress = 0;
			int maxProgress = fort63->numNodes;
			int onePercent = 0.01*maxProgress;
			emit progressStartValue(0);
			emit progressEndValue(maxProgress);
			emit readingInProgress(true);

			fileStream.seek(tsStart);
			int node;
			float elevation;
			for (int i=0; i<fort63->numNodes; ++i)
			{
				fileStream >> node;
				fileStream >> elevation;
				fort63->elevations[node-1] = elevation;

				++currProgress;
				if (currProgress % onePercent == 0)
					emit progress(currProgress);
			}

			fort63->currentTimestep = ts;
			emit readingInProgress(false);
			emit timestepLoaded(fort63, ts);

		}
	}
}





































