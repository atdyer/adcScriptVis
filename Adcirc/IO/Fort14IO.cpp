#include "Fort14IO.h"

Fort14IO::Fort14IO(Fort14 *fort14, QString fileLocation, QProgressBar *progressBar) :
	QObject(0)
{
	this->fort14 = fort14;
	fileLoc = fileLocation;
	this->progressBar = progressBar;

	if (progressBar)
		connect(this, SIGNAL(progress(int)), progressBar, SLOT(setValue(int)));

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
	fileStream >> fort14->_numElements;
	fileStream >> fort14->_numNodes;
	fileStream.readLine();

	// Set up progress bar variables
	int currProgress = 0;
	int maxProgress = fort14->_numNodes + fort14->_numElements;
	int onePercent = 0.01 * maxProgress;
	if (progressBar)
	{
		progressBar->setVisible(true);
		progressBar->setValue(0);
		progressBar->setMaximum(maxProgress);
	}

	// Read the nodes
	fort14->nodes.reserve(fort14->_numNodes);
	for (int i=0; i<fort14->_numNodes; ++i)
	{
		Node currNode;
		fileStream >> currNode.nodeNumber;
		fileStream >> currNode.x;
		fileStream >> currNode.y;
		fileStream >> currNode.z;
		fileStream.readLine();

		fort14->nodes.append(currNode);

		++currProgress;
		if (currProgress % onePercent == 0)
			emit progress(currProgress);
	}
	fort14->nodes.squeeze();

	// Read the elements
	fort14->elements.reserve(fort14->_numElements);
	int trash;
	for (int i=0; i<fort14->_numElements; ++i)
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

	if (progressBar)
		progressBar->setVisible(false);

	emit fort14Loaded(fort14);
}


