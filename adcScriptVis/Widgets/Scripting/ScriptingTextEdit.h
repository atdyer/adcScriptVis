#ifndef SCRIPTINGTEXTEDIT_H
#define SCRIPTINGTEXTEDIT_H

#include <QTextEdit>
#include <QCompleter>
#include <QAbstractItemView>
#include <QKeyEvent>
#include <QScrollBar>
#include <QStringListModel>
#include <QFileSystemModel>
#include <QtDebug>

class ScriptingTextEdit : public QTextEdit
{
		Q_OBJECT
	public:
		explicit ScriptingTextEdit(QWidget *parent = 0);

		void		setCompleter(QCompleter *newCompleter);
		QCompleter	*getCompleter() const;

	protected:
		void	keyPressEvent(QKeyEvent *e);
		void	focusInEvent(QFocusEvent *e);

	private slots:
		void	insertCompletion(const QString &completion);

	private:
		QString textUnderCursor() const;

		QCompleter *completer;

};

#endif // SCRIPTINGTEXTEDIT_H
