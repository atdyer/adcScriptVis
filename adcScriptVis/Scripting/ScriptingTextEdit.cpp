#include "ScriptingTextEdit.h"

ScriptingTextEdit::ScriptingTextEdit(QWidget *parent) :
	QPlainTextEdit(parent), completer(0), lineNumberArea(0)
{
	lineNumberArea = new LineNumberArea(this);

	connect(this, SIGNAL(blockCountChanged(int)), this, SLOT(updateLineNumberAreaWidth(int)));
	connect(this, SIGNAL(updateRequest(QRect,int)), this, SLOT(updateLineNumberArea(QRect,int)));
	connect(this, SIGNAL(cursorPositionChanged()), this, SLOT(highlightCurrentLine()));

	updateLineNumberAreaWidth(0);
	highlightCurrentLine();
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


void ScriptingTextEdit::lineNumberAreaPaintEvent(QPaintEvent *e)
{
	QPainter painter(lineNumberArea);
	painter.fillRect(e->rect(), QColor(Qt::darkGray).darker());

	QTextBlock block = firstVisibleBlock();
	int blockNumber = block.blockNumber();
	int top = (int) blockBoundingGeometry(block).translated(contentOffset()).top();
	int bottom = top + (int) blockBoundingRect(block).height();

	while (block.isValid() && top <= e->rect().bottom())
	{
		if (block.isVisible() && bottom >= e->rect().top())
		{
			QString number = QString::number(blockNumber + 1);
			painter.setPen(Qt::black);
			painter.drawText(0, top, lineNumberArea->width()-3, fontMetrics().height(),
					 Qt::AlignRight, number);
		}

		block = block.next();
		top = bottom;
		bottom = top + (int) blockBoundingRect(block).height();
		++blockNumber;
	}
}


int ScriptingTextEdit::lineNumberAreaWidth()
{
	int digits = 1;
	int max = qMax(1, blockCount());
	while (max >= 10) {
		max /= 10;
		++digits;
	}

	int space = 6 + fontMetrics().width(QLatin1Char('9'))*digits;
	return space;
}


QString ScriptingTextEdit::textUnderCursor() const
{
	QTextCursor cursor = textCursor();
	cursor.select(QTextCursor::LineUnderCursor);
	return cursor.selectedText().split(QRegularExpression("\\(|\\s|\\n|\u2029")).last();
}


void ScriptingTextEdit::focusInEvent(QFocusEvent *e)
{
	if (completer)
		completer->setWidget(this);
	QPlainTextEdit::focusInEvent(e);
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
		QPlainTextEdit::keyPressEvent(e);

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


void ScriptingTextEdit::resizeEvent(QResizeEvent *e)
{
	QPlainTextEdit::resizeEvent(e);

	QRect cr = contentsRect();
	lineNumberArea->setGeometry(QRect(cr.left(), cr.top(), lineNumberAreaWidth(),
					  cr.height()));
}


void ScriptingTextEdit::insertCompletion(const QString &completion)
{
	if (!completer || completer->widget() != this)
		return;
	QTextCursor cursor = textCursor();
	while (cursor.movePosition(QTextCursor::Left, QTextCursor::KeepAnchor))
	{
		if (cursor.selectedText().contains(QRegularExpression("\\(|\\s|\\n|\u2029")))
		{
			cursor.movePosition(QTextCursor::Right, QTextCursor::KeepAnchor);
			break;
		}
	}
	cursor.removeSelectedText();
	cursor.insertText(completion);
	setTextCursor(cursor);
}


void ScriptingTextEdit::highlightCurrentLine()
{
	QList<QTextEdit::ExtraSelection> extraSelections;

	if (!isReadOnly())
	{
		QTextEdit::ExtraSelection selection;
		QColor lineColor = QColor("#201F1F").lighter();
		selection.format.setBackground(lineColor);
		selection.format.setProperty(QTextFormat::FullWidthSelection, true);
		selection.cursor = textCursor();
		selection.cursor.clearSelection();
		extraSelections.append(selection);
	}
	setExtraSelections(extraSelections);
}


void ScriptingTextEdit::updateLineNumberAreaWidth(int)
{
	setViewportMargins(lineNumberAreaWidth(), 0, 0, 0);
}


void ScriptingTextEdit::updateLineNumberArea(const QRect &rect, int dy)
{
	if (dy)
		lineNumberArea->scroll(0, dy);
	else
		lineNumberArea->update(0, rect.y(), lineNumberArea->width(), rect.height());

	if (rect.contains(viewport()->rect()))
		updateLineNumberAreaWidth(0);
}


































