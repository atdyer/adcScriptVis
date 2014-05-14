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
	delete ui;
}


void ScriptingWidget::BuildWidget()
{
	ui->verticalLayout->setContentsMargins(0, 0, 0, 0);

	// Create the toolbar
	QToolBar *toolBar = new QToolBar();
	toolBar->setContentsMargins(0, 0, 0, 0);
	ui->verticalLayout->addWidget(toolBar);

	// Create the text editor
	ScriptingTextEdit *textEdit = new ScriptingTextEdit();
	ui->verticalLayout->addWidget(textEdit);

	// Create Actions
	QAction *runAction = new QAction(tr("Run Script"), 0);
	QAction *saveAction = new QAction(tr("Save Script"), 0);
	QAction *openAction = new QAction(tr("Open Script"), 0);
	QWidget *spacer = new QWidget();
	QAction *helpAction = new QAction(tr("Help"), 0);

	// Set up connections and such
	spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

	// Add actions to the toolbar
	toolBar->addAction(runAction);
	toolBar->addAction(saveAction);
	toolBar->addAction(openAction);
	toolBar->addWidget(spacer);
	toolBar->addAction(helpAction);
}
