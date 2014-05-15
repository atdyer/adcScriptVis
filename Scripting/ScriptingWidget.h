#ifndef SCRIPTINGWIDGET_H
#define SCRIPTINGWIDGET_H

#include <QWidget>
#include <QToolBar>
#include <QAction>
#include <QPushButton>
#include <QSettings>
#include "Scripting/ScriptingTextEdit.h"

namespace Ui {
	class ScriptingWidget;
}

class ScriptingWidget : public QWidget
{
		Q_OBJECT

	public:
		explicit ScriptingWidget(QWidget *parent = 0);
		~ScriptingWidget();

	private:
		Ui::ScriptingWidget *ui;

		void	BuildWidget();
		void	BuildToolbar();
		void	LoadSettings();
		void	SaveSettings();
};

#endif // SCRIPTINGWIDGET_H
