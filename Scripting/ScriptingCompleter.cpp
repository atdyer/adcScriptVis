#include "ScriptingCompleter.h"

ScriptingCompleter::ScriptingCompleter(QObject *parent) :
	QCompleter(parent)
{
}


ScriptingCompleter::ScriptingCompleter(QAbstractItemModel *model, QObject *parent) :
	QCompleter(model, parent)
{
}


QString ScriptingCompleter::pathFromIndex(const QModelIndex &index) const
{
	QStringList dataList;
	for (QModelIndex i=index; i.isValid(); i=i.parent())
	{
		dataList.prepend(model()->data(i, completionRole()).toString());
	}
	return dataList.join(".");
}


QStringList ScriptingCompleter::splitPath(const QString &path) const
{
	return path.split(".");
}
