#include "ScriptingWidget.h"
#include "ui_ScriptingWidget.h"

ScriptingWidget::ScriptingWidget(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::ScriptingWidget),
	completer(new ScriptingCompleter(this)),
	scriptingEngine(new QScriptEngine(this)),
	toolBar(new QToolBar()),
	runAction(new QAction(tr("Run Script"), this)),
	saveAction(new QAction(tr("Save Script"), this)),
	openAction(new QAction(tr("Open Script"), this)),
	spacer(new QWidget(this)),
	editorButton(new QPushButton("Editor", this)),
	consoleButton(new QPushButton("Console", this)),
	group(new QButtonGroup(this))
{
	ui->setupUi(this);

	BuildWidget();

	// Hook up the completer
	if (completer)
		completer->setModel(ui->availableObjectsList->model());

//	Fort14 *test = new Fort14(this);
//	AddScriptableObject(test);
}

ScriptingWidget::~ScriptingWidget()
{
	SaveSettings();
	delete ui;
}


void ScriptingWidget::AddScriptableObject(QObject *newObject)
{
	if (newObject)
	{
		const QMetaObject *mo = newObject->metaObject();

		ui->scriptConsole->addScriptableObject(newObject);

		// Add the object to the list of available objects
		QTreeWidgetItem *top = new QTreeWidgetItem(ui->availableObjectsList);
		top->setText(0, newObject->objectName());
		top->setText(1, mo->className());

		for (int i=mo->propertyOffset(); i<mo->propertyCount(); ++i)
		{
			QTreeWidgetItem *property = new QTreeWidgetItem(top);
			property->setText(0, mo->property(i).name());
			property->setText(1, mo->property(i).typeName());
		}

		for (int i=mo->methodOffset(); i<mo->methodCount(); ++i)
		{
			QTreeWidgetItem *method = new QTreeWidgetItem(top);
			method->setText(0, mo->method(i).methodSignature());
			method->setText(1, mo->method(i).typeName());
		}

		ui->availableObjectsList->expandAll();
		ui->availableObjectsList->resizeColumnToContents(0);
	}

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
	// Build the toolbar
	toolBar->setContentsMargins(0, 0, 0, 0);
	toolBar->setStyleSheet("QToolButton:pressed {"
				"background-color: #4A4949;"
				"border: 1px solid silver;"
				"border-radius: 3px;"
				"}");
	ui->toolbarLayout->addWidget(toolBar);

	// Build Actions
	editorButton->setCheckable(true);
	editorButton->setChecked(false);
	consoleButton->setCheckable(true);
	consoleButton->setChecked(true);
	showConsole();
	group->addButton(editorButton);
	group->addButton(consoleButton);
	group->setExclusive(true);

	// Set up connections and such
	spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	connect(runAction, SIGNAL(triggered()), this, SLOT(executeEditorScript()));
	connect(editorButton, SIGNAL(clicked()), this, SLOT(showEditor()));
	connect(consoleButton, SIGNAL(clicked()), this, SLOT(showConsole()));

	// Add actions to the toolbar
	toolBar->addAction(runAction);
	toolBar->addAction(saveAction);
	toolBar->addAction(openAction);
	toolBar->addWidget(spacer);
	toolBar->addWidget(editorButton);
	toolBar->addWidget(consoleButton);
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


void ScriptingWidget::executeEditorScript()
{
	if (ui->scriptConsole)
	{
		showConsole();
		ui->scriptConsole->executeCode(ui->scriptEditor->document()->toPlainText());
	}
}


void ScriptingWidget::showEditor()
{
	if (!editorButton->isChecked())
		editorButton->setChecked(true);
	ui->stackedWidget->setCurrentIndex(0);
	ui->scriptEditor->setCompleter(completer);
}


void ScriptingWidget::showConsole()
{
	if (!consoleButton->isChecked())
		consoleButton->setChecked(true);
	ui->stackedWidget->setCurrentIndex(1);
	ui->scriptConsole->setCompleter(completer);
}
