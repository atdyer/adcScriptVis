#include "ScriptingWidget.h"
#include "ui_ScriptingWidget.h"

ScriptingWidget::ScriptingWidget(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::ScriptingWidget)
{
	ui->setupUi(this);

	BuildWidget();
}

ScriptingWidget::~ScriptingWidget()
{
	SaveSettings();
	delete ui;
}


void ScriptingWidget::BuildWidget()
{
	ui->splitter->setStretchFactor(0, 1);
	ui->splitter->setStretchFactor(1, 4);
	BuildToolbar();
	LoadSettings();
}


void ScriptingWidget::BuildToolbar()
{
	// Create the toolbar
	QToolBar *toolBar = new QToolBar();
	toolBar->setContentsMargins(0, 0, 0, 0);
	ui->toolbarLayout->addWidget(toolBar);

	// Create Actions
	QAction *runAction = new QAction(tr("Run Script"), this);
	QAction *saveAction = new QAction(tr("Save Script"), this);
	QAction *openAction = new QAction(tr("Open Script"), this);
	QWidget *spacer = new QWidget(this);
//	QAction *helpAction = new QAction(tr("Help"), 0);
	QButtonGroup *group = new QButtonGroup(this);
	QPushButton *editorButton = new QPushButton("Editor", this);
	QPushButton *consoleButton = new QPushButton("Console", this);
	editorButton->setCheckable(true);
	editorButton->setChecked(true);
	consoleButton->setCheckable(true);
	consoleButton->setChecked(false);
	group->addButton(editorButton);
	group->addButton(consoleButton);
	group->setExclusive(true);

	// Set up connections and such
	spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

	// Add actions to the toolbar
	toolBar->addAction(runAction);
	toolBar->addAction(saveAction);
	toolBar->addAction(openAction);
	toolBar->addWidget(spacer);
	toolBar->addWidget(editorButton);
	toolBar->addWidget(consoleButton);
//	toolBar->addAction(helpAction);
}


void ScriptingWidget::LoadSettings()
{
	QSettings settings;
	ui->splitter->restoreState(settings.value("scripting/splitter").toByteArray());

}


void ScriptingWidget::SaveSettings()
{
	QSettings settings;
	settings.setValue("scripting/splitter", ui->splitter->saveState());
}
