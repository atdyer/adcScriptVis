#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSettings>
#include <QThreadPool>
#include <QModelIndex>

#include "Adcirc/AdcircFileManager.h"
#include "Adcirc/Fort14.h"
#include "Adcirc/Fort63.h"
#include "Layers/LayerStack.h"
#include "Layers/MeshLayer.h"
#include "OpenGL/Shaders/SolidShader.h"
#include "OpenGL/Shaders/GradientShader.h"

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
		AdcircFileManager	fileManager;

		void	connectActions();
		void	initializeLayout();
		void	loadSettings();
		void	saveSettings();

	protected slots:

		void	fort14Loaded(Fort14 *newFort14);
		void	fort63Loaded(Fort63 *newFort63, int ts);
		void	setFullScreen(bool fs);
		void	treeDoubleClicked(QModelIndex index);

};

#endif // MAINWINDOW_H
