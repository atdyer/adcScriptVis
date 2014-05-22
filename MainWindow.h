#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSettings>
#include <QThreadPool>
#include <QModelIndex>

#include "Adcirc/Fort14.h"
#include "Adcirc/IO/Fort14IO.h"
#include "Layers/LayerStack.h"
#include "Layers/MeshLayer.h"

namespace Ui {
	class MainWindow;
}

class MainWindow : public QMainWindow
{
		Q_OBJECT

	public:
		explicit MainWindow(QWidget *parent = 0);
		~MainWindow();

	private:
		Ui::MainWindow *ui;

		void	connectActions();
		void	initializeLayout();
		void	loadSettings();
		void	saveSettings();

	protected slots:

		void	fort14Loaded(Fort14 *newFort14);
		void	setFullScreen(bool fs);
		void	treeDoubleClicked(QModelIndex index);

};

#endif // MAINWINDOW_H
