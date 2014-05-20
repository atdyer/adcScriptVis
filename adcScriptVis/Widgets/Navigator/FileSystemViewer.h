#ifndef FILESYSTEMVIEWER_H
#define FILESYSTEMVIEWER_H

#include <QTreeView>
#include <QFileSystemModel>
#include <QHeaderView>
#include <QTimer>

class FileSystemViewer : public QTreeView
{
		Q_OBJECT
	public:
		explicit FileSystemViewer(QWidget *parent = 0);

	private:

		QFileSystemModel	*model;

		void	createModel();
		void	createFileFilters();
		void	connectModel();

	signals:

	public slots:

	protected slots:

		void	fitAllColumns();

};

#endif // FILESYSTEMVIEWER_H
