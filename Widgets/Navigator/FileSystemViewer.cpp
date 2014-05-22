#include "FileSystemViewer.h"

FileSystemViewer::FileSystemViewer(QWidget *parent) :
	QTreeView(parent)
{
	header()->setStretchLastSection(false);

	createModel();
	createFileFilters();
	connectModel();
}


QFileSystemModel *FileSystemViewer::fileSystemModel()
{
	return model;
}


void FileSystemViewer::createModel()
{
	model = new QFileSystemModel(this);
	model->setRootPath("/home/tristan/Adcirc/");
}


void FileSystemViewer::createFileFilters()
{
	QStringList filters;
	filters << "*.14";

	if (model)
	{
		model->setNameFilters(filters);
		model->setNameFilterDisables(false);
	}
}


void FileSystemViewer::connectModel()
{
	setModel(model);
	setRootIndex(model->index("/home/tristan/Adcirc"));
	setSortingEnabled(true);
	hideColumn(2);
	sortByColumn(0, Qt::AscendingOrder);

	QTimer::singleShot(10, this, SLOT(fitAllColumns()));
}


void FileSystemViewer::fitAllColumns()
{
	if (model)
	{
		for (int i=0; i<model->columnCount(); ++i)
		{
			resizeColumnToContents(i);
		}
	}
}
