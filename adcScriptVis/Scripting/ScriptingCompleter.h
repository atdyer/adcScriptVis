#ifndef SCRIPTINGCOMPLETER_H
#define SCRIPTINGCOMPLETER_H

#include <QCompleter>

class ScriptingCompleter : public QCompleter
{
		Q_OBJECT
	public:
		explicit ScriptingCompleter(QObject *parent = 0);
		ScriptingCompleter(QAbstractItemModel *model, QObject *parent = 0);

		virtual QString		pathFromIndex(const QModelIndex &index) const;
		virtual QStringList	splitPath(const QString &path) const;

	signals:

	public slots:

};

#endif // SCRIPTINGCOMPLETER_H
