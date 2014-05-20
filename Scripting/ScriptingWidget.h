#ifndef SCRIPTINGWIDGET_H
#define SCRIPTINGWIDGET_H

#include <QWidget>
#include <QToolBar>
#include <QAction>
#include <QPushButton>
#include <QSettings>
#include <QDebug>
#include <QMetaProperty>
#include <QScriptEngine>

#include "Scripting/ScriptingTextEdit.h"
#include "Scripting/ScriptingCompleter.h"
#include "Scripting/ScriptingFunctions.h"
#include "Adcirc/Fort14.h"

namespace Ui {
	class ScriptingWidget;
}

class ScriptingWidget : public QWidget
{
		Q_OBJECT

	public:
		explicit ScriptingWidget(QWidget *parent = 0);
		~ScriptingWidget();

		void	AddScriptableObject(QObject *newObject);

	private:
		Ui::ScriptingWidget *ui;

		ScriptingCompleter	*completer;
		QScriptEngine		*scriptingEngine;

		QToolBar *toolBar;
		QAction	*runAction;
		QAction	*saveAction;
		QAction *openAction;
		QWidget *spacer;
		QPushButton *editorButton;
		QPushButton *consoleButton;
		QButtonGroup *group;

		void	BuildWidget();
		void	BuildToolbar();
		void	LoadSettings();
		void	SaveSettings();

	private slots:

		void	executeEditorScript();
		void	showConsole();
		void	showEditor();
};

#endif // SCRIPTINGWIDGET_H
