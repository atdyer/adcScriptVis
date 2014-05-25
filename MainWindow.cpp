#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	connectActions();
	initializeLayout();
	loadSettings();
}

MainWindow::~MainWindow()
{
	saveSettings();

	delete ui;
}


void MainWindow::connectActions()
{
	// Connect the scripting dock widget to the action menu item
	connect(ui->actionScriptingToggle, SIGNAL(toggled(bool)), ui->dockWidget, SLOT(setVisible(bool)));
	connect(ui->dockWidget, SIGNAL(visibilityChanged(bool)), ui->actionScriptingToggle, SLOT(setChecked(bool)));

	// Connect the full screen action item
	connect(ui->actionFull_Screen, SIGNAL(toggled(bool)), this, SLOT(setFullScreen(bool)));

	// Connect tree double-click on file
	connect(ui->treeView, SIGNAL(doubleClicked(QModelIndex)), this, SLOT(treeDoubleClicked(QModelIndex)));

	// Connect camera changes
	connect(ui->button2D, SIGNAL(clicked()), ui->glPanel, SLOT(use2DCamera()));
	connect(ui->button3D, SIGNAL(clicked()), ui->glPanel, SLOT(use3DCamera()));

	// Connect the exit action
	connect(ui->actionExit, SIGNAL(triggered()), this, SLOT(close()));
}


void MainWindow::initializeLayout()
{
	// Set the proportions of the left and right panes
	ui->splitter->setStretchFactor(0, 1);
	ui->splitter->setStretchFactor(1, 8);

	// Hide the progress bar
	ui->progressBar->setVisible(false);
}


void MainWindow::loadSettings()
{
	QSettings settings;

	restoreGeometry(settings.value("window/geometry").toByteArray());
	restoreState(settings.value("window/windowState").toByteArray());
	ui->splitter->restoreState(settings.value("window/splitter").toByteArray());
	ui->dockWidget->setVisible(true);
	ui->actionFull_Screen->setChecked(isFullScreen());

}


void MainWindow::saveSettings()
{
	QSettings settings;
	settings.setValue("window/geometry", saveGeometry());
	settings.setValue("window/windowState", saveState());
	settings.setValue("window/splitter", ui->splitter->saveState());
}


void MainWindow::fort14Loaded(Fort14 *newFort14)
{
	newFort14->setParent(this);
	ui->scriptingWidget->AddScriptableObject(newFort14);
	ui->glPanel->setObjectName("displayPanel");
	ui->scriptingWidget->AddScriptableObject(ui->glPanel);

	/////////////// TESTING /////////////////////
	LayerStack *testStack = new LayerStack(this);
	MeshLayer *testMesh = new MeshLayer(this);
	SolidShader *outlineShader = new SolidShader(this);
//	SolidShader *fillShader = new SolidShader(this);
	GradientShader *fillShader = new GradientShader(this);

	QColor outlineColor (0.2*255, 0.2*255, 0.2*255, 0.1*255);

	float minZ = newFort14->getMinZ();
	float maxZ = newFort14->getMaxZ();
	float zDiff = maxZ - minZ;
	QGradientStops stops;

	float percentage;
	float elevations[] = {minZ/zDiff, 0.0/zDiff, 0.5/zDiff, 1.75/zDiff, -0.5/zDiff, maxZ/zDiff};
	QColor colors[] = {QColor::fromRgb(0, 0, 255),
			   QColor::fromRgb(255,255,255),
			   QColor::fromRgb(0,255,0),
			   QColor::fromRgb(0,175,0),
			   QColor::fromRgb(0,255,255),
			   QColor::fromRgb(0, 100, 0)};
	for (unsigned int i=0; i<6; ++i)
	{
		percentage = (maxZ - elevations[i])/(maxZ-minZ);
		stops << QGradientStop(percentage, colors[i]);
	}

	outlineShader->setColor(outlineColor);
	fillShader->setGradientRange(minZ, maxZ);
	fillShader->setGradientStops(stops);

//	QColor fillColor (Qt::green);
//	fillShader->setColor(fillColor);

	testMesh->setVertices(newFort14->getNodes());
	testMesh->setIndices(newFort14->getElements());
	testMesh->setOutlineShader(outlineShader);
	testMesh->setFillShader(fillShader);

	testStack->appendLayer(testMesh);

	ui->glPanel->setCurrentLayerStack(testStack);
}


void MainWindow::setFullScreen(bool fs)
{
	if (fs)
		showFullScreen();
	else
		showNormal();
}

void MainWindow::treeDoubleClicked(QModelIndex index)
{
	QFileInfo info = ui->treeView->fileSystemModel()->fileInfo(index);
	if (!info.isDir())
	{
		if (info.suffix() == QString("14"))
		{
			Fort14 *fort14 = new Fort14();
			Fort14IO *reader = new Fort14IO(fort14, info.absoluteFilePath());

			connect(reader, SIGNAL(progressStartValue(int)), ui->progressBar, SLOT(setMinimum(int)));
			connect(reader, SIGNAL(progressEndValue(int)), ui->progressBar, SLOT(setMaximum(int)));
			connect(reader, SIGNAL(readingInProgress(bool)), ui->progressBar, SLOT(setVisible(bool)));
			connect(reader, SIGNAL(progress(int)), ui->progressBar, SLOT(setValue(int)));
			connect(reader, SIGNAL(fort14Loaded(Fort14*)), this, SLOT(fort14Loaded(Fort14*)));

			QThreadPool::globalInstance()->start(reader);
		}
	}
}


















