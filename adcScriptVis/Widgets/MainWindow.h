#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSettings>

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

		void	setFullScreen(bool fs);
};

#endif // MAINWINDOW_H
