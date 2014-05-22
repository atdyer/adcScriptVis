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

	/////////////// TESTING /////////////////////
	LayerStack *testStack = new LayerStack(this);
	MeshLayer *testMesh = new MeshLayer(this);
	SolidShader *outlineShader = new SolidShader(this);
	SolidShader *fillShader = new SolidShader(this);

	QColor outlineColor (0.2*255, 0.2*255, 0.2*255, 0.1*255);
	QColor fillColor (Qt::green);
	outlineShader->setColor(outlineColor);
	fillShader->setColor(fillColor);

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
			Fort14IO *reader = new Fort14IO(fort14, info.absoluteFilePath(), ui->progressBar);
			connect(reader, SIGNAL(fort14Loaded(Fort14*)), this, SLOT(fort14Loaded(Fort14*)));

			QThreadPool::globalInstance()->start(reader);
		}
	}
}


















