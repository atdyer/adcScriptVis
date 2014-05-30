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

	// Connect the Adcirc file manager
	fileManager.setProgressBar(ui->progressBar);
	connect(&fileManager, SIGNAL(meshLayerLoaded(MeshLayerAdcirc*)), this, SLOT(meshLayerLoaded(MeshLayerAdcirc*)));

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

	// Add existing components to scripting engine
	ui->glPanel->setObjectName("displayPanel");
	ui->scriptingWidget->AddScriptableObject(ui->glPanel);
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


void MainWindow::meshLayerLoaded(MeshLayerAdcirc *meshLayer)
{
	if (meshLayer)
	{
		Fort14 *newFort14 = meshLayer->getFort14();
		ui->scriptingWidget->AddScriptableObject(newFort14);
		LayerStack *testStack = new LayerStack(this);
		SolidShader *outlineShader = new SolidShader(false, this);
		GradientShader *fillShader = new GradientShader(false, this);
		GradientShader *waterFill = new GradientShader(true, this);

		// Outline Color
		QColor outlineColor (0.2*255, 0.2*255, 0.2*255, 0.1*255);

		// Terrain Color
		float minZ = newFort14->getMinZ();
		float maxZ = newFort14->getMaxZ();
		float zDiff = maxZ - minZ;
		QGradientStops stops;

		float percentage;
		float elevations[] = {minZ/zDiff, 0.0f/zDiff, 0.5f/zDiff, 1.75f/zDiff, -0.5f/zDiff, maxZ/zDiff};
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

		// Water Color
		QGradientStops waterStops;
		waterStops << QGradientStop(0.0, QColor::fromRgb(255, 0, 0, 0.4*255));
		waterStops << QGradientStop(1.0, QColor::fromRgb(0, 0, 255, 0.4*255));

		outlineShader->setColor(outlineColor);
		fillShader->setGradientRange(minZ, maxZ);
		fillShader->setGradientStops(stops);
		waterFill->setGradientRange(-0.1, 0.1);
		waterFill->setGradientStops(waterStops);

		meshLayer->appendShader(fillShader, GL_FILL);
		meshLayer->appendShader(outlineShader, GL_LINE);
		meshLayer->appendShader(waterFill, GL_FILL);

		testStack->appendLayer(meshLayer);

		ui->glPanel->setCurrentLayerStack(testStack);

	}
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
		fileManager.openFile(info);
	}
}


















