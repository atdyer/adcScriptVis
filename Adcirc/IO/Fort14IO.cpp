#include "Fort14IO.h"

Fort14IO::Fort14IO(Fort14 *fort14, QString fileLocation) :
	QObject(0)
{
	this->fort14 = fort14;
	fileLoc = fileLocation;
}

Fort14IO::~Fort14IO()
{
}

void Fort14IO::run()
{
	QFile file (fileLoc);
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		emit fort14Loaded(0);
		return;
	}

	QTextStream fileStream (&file);

	// Read the header
	fort14->setGridID(fileStream.readLine());
	fileStream >> fort14->numElements;
	fileStream >> fort14->numNodes;
	fileStream.readLine();

	// Set up progress bar variables
	int currProgress = 0;
	int maxProgress = 2*fort14->numNodes + fort14->numElements;
	int onePercent = 0.01 * maxProgress;
	emit progressStartValue(0);
	emit progressEndValue(maxProgress);
	emit readingInProgress(true);

	// Read the nodes
	float minX = 99999.0;
	float maxX = -99999.0;
	float minY = 99999.0;
	float maxY = -99999.0;
	float minZ = 99999.0;
	float maxZ = -99999.0;
	fort14->nodes.reserve(fort14->numNodes);
	for (int i=0; i<fort14->numNodes; ++i)
	{
		Node currNode;
		fileStream >> currNode.nodeNumber;
		fileStream >> currNode.x;
		fileStream >> currNode.y;
		fileStream >> currNode.z;
		fileStream.readLine();

		if (currNode.x > maxX)
			maxX = currNode.x;
		else if (currNode.x < minX)
			minX = currNode.x;
		if (currNode.y > maxY)
			maxY = currNode.y;
		else if (currNode.y < minY)
			minY = currNode.y;
		currNode.z *= -1.0;
		if (currNode.z > maxZ)
			maxZ = currNode.z;
		else if (currNode.z < minZ)
			minZ = currNode.z;

		fort14->nodes.append(currNode);

		++currProgress;
		if (currProgress % onePercent == 0)
			emit progress(currProgress);
	}
	fort14->nodes.squeeze();
	fort14->maxZ = maxZ;
	fort14->minZ = minZ;

	// Normalize the nodes
	float midX = minX + (maxX - minX) / 2.0;
	float midY = minY + (maxY - minY) / 2.0;
	float max = qMax(maxX-minX, maxY-minY);
	float diffZ = maxZ - minZ;
	for (int i=0; i<fort14->numNodes; ++i)
	{
		fort14->nodes[i].x = (fort14->nodes[i].x - midX) / max;
		fort14->nodes[i].y = (fort14->nodes[i].y - midY) / max;
		fort14->nodes[i].z = (fort14->nodes[i].z) / diffZ;
		++currProgress;
		if (currProgress % onePercent == 0)
			emit progress(currProgress);
	}

	// Read the elements
	fort14->elements.reserve(fort14->numElements);
	int trash;
	for (int i=0; i<fort14->numElements; ++i)
	{
		Element currElement;
		fileStream >> currElement.elementNumber;
		fileStream >> trash;
		fileStream >> currElement.n1;
		fileStream >> currElement.n2;
		fileStream >> currElement.n3;
		fileStream.readLine();

		fort14->elements.append(currElement);

		++currProgress;
		if (currProgress % onePercent == 0)
			emit progress(currProgress);
	}
	fort14->elements.squeeze();

	file.close();

	emit readingInProgress(false);
	emit fort14Loaded(fort14);
}


