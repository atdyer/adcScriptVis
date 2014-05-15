#include "ScriptingTextEdit.h"

ScriptingTextEdit::ScriptingTextEdit(QWidget *parent) :
	QTextEdit(parent), completer(0)
{
	QCompleter *testCompleter = new QCompleter(this);

//	QStringList words;
//	words.append("Hello");

//	QStringListModel *model = new QStringListModel(words, testCompleter);

//	testCompleter->setModel(model);

	QFileSystemModel *model = new QFileSystemModel(testCompleter);
	model->setRootPath("");

	testCompleter->setModel(model);

	setCompleter(testCompleter);
}


void ScriptingTextEdit::setCompleter(QCompleter *newCompleter)
{
	if (completer)
		disconnect(completer, 0, this, 0);

	completer = newCompleter;

	if (!completer)
		return;

	completer->setWidget(this);
	completer->setCompletionMode(QCompleter::PopupCompletion);
	completer->setCaseSensitivity(Qt::CaseInsensitive);
	connect(completer, SIGNAL(activated(QString)), this, SLOT(insertCompletion(QString)));
}


QCompleter *ScriptingTextEdit::getCompleter() const
{
	return completer;
}


void ScriptingTextEdit::insertCompletion(const QString &completion)
{
	if (completer->widget() != this)
		return;
	QTextCursor cursor = textCursor();
	cursor.select(QTextCursor::BlockUnderCursor);
	cursor.removeSelectedText();
	cursor.insertText(completion);
	setTextCursor(cursor);
}


QString ScriptingTextEdit::textUnderCursor() const
{
	QTextCursor cursor = textCursor();
	cursor.select(QTextCursor::BlockUnderCursor);
	return cursor.selectedText();
}


void ScriptingTextEdit::focusInEvent(QFocusEvent *e)
{
	if (completer)
		completer->setWidget(this);
	QTextEdit::focusInEvent(e);
}


void ScriptingTextEdit::keyPressEvent(QKeyEvent *e)
{
	if (completer && completer->popup()->isVisible())
	{
		switch (e->key())
		{
			case Qt::Key_Enter:
			case Qt::Key_Return:
			case Qt::Key_Escape:
			case Qt::Key_Tab:
			case Qt::Key_Backtab:
				e->ignore();
				return;
			default:
				break;
		}
	}

	bool isShortcut = ((e->modifiers() & Qt::ControlModifier) && e->key() == Qt::Key_Space);

	if (!completer || !isShortcut)
		QTextEdit::keyPressEvent(e);

	const bool ctrlOrShift = e->modifiers() & (Qt::ControlModifier | Qt::ShiftModifier);
	if (!completer || (ctrlOrShift && e->text().isEmpty()))
		return;

//	static QString eow("~!@#$%^&*()_+{}|:\"<>?,./;'[]\\-="); // end of word
	static QString eow("~!@#$%^&*()_+{}|:\"<>?,;'[]\\-=");
	bool hasModifier = (e->modifiers() != Qt::NoModifier) && !ctrlOrShift;
	QString completionPrefix = textUnderCursor();

	if (!isShortcut && (hasModifier || e->text().isEmpty()|| completionPrefix.length() < 1
			    || eow.contains(e->text().right(1))))
	{
		completer->popup()->hide();
		return;
	}

	if (completionPrefix != completer->completionPrefix())
	{
		completer->setCompletionPrefix(completionPrefix);
		completer->popup()->setCurrentIndex(completer->completionModel()->index(0, 0));
	}

	QRect cr = cursorRect();
	cr.setWidth(completer->popup()->sizeHintForColumn(0) +
		    completer->popup()->verticalScrollBar()->sizeHint().width());
	completer->complete(cr);
}

































