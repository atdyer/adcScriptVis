#ifndef SCRIPTINGTEXTEDIT_H
#define SCRIPTINGTEXTEDIT_H

#include <QPlainTextEdit>
#include <QCompleter>
#include <QAbstractItemView>
#include <QKeyEvent>
#include <QScrollBar>
#include <QStringListModel>
#include <QFileSystemModel>
#include <QPainter>
#include <QRegularExpression>
#include <QTextBlock>
#include <QtDebug>

class LineNumberArea;

class ScriptingTextEdit : public QPlainTextEdit
{
		Q_OBJECT
	public:

		explicit ScriptingTextEdit(QWidget *parent = 0);

		void		setCompleter(QCompleter *newCompleter);
		QCompleter	*getCompleter() const;
		void		lineNumberAreaPaintEvent(QPaintEvent *e);
		int		lineNumberAreaWidth();

	protected:

		void	focusInEvent(QFocusEvent *e);
		void	keyPressEvent(QKeyEvent *e);
		void	resizeEvent(QResizeEvent *e);

	private slots:

		void	insertCompletion(const QString &completion);
		void	highlightCurrentLine();
		void	updateLineNumberAreaWidth(int);
		void	updateLineNumberArea(const QRect &rect, int dy);

	private:
		QString textUnderCursor() const;

		QCompleter *completer;
		QWidget *lineNumberArea;

};

class LineNumberArea : public QWidget
{
	public:
		LineNumberArea(ScriptingTextEdit *editor) : QWidget(editor) {
			codeEditor = editor;
		}

		QSize sizeHint() const {
			return QSize(codeEditor->lineNumberAreaWidth(), 0);
		}

	protected:
		void paintEvent(QPaintEvent *event) {
			codeEditor->lineNumberAreaPaintEvent(event);
		}

	private:
		ScriptingTextEdit *codeEditor;
};

#endif // SCRIPTINGTEXTEDIT_H
