#include "ScriptingConsole.h"

ScriptingConsole::ScriptingConsole(QWidget *parent) :
	QTextEdit(parent),
	completer(0),
	engine(new QScriptEngine(this)),
	lineHeader(">> ")
{
	setAcceptRichText(false);
	setUndoRedoEnabled(false);
	insertPlainText(lineHeader);
	initializeScriptingEngine();
}


void ScriptingConsole::addScriptableObject(QObject *newObject)
{
	const QMetaObject *mo = newObject->metaObject();

	// Add the object to the scripting engine
	QScriptValue objValue = engine->newQObject(newObject);
	engine->globalObject().setProperty(newObject->objectName(), objValue);
}


void ScriptingConsole::executeCode(QString code)
{
	if (engine)
	{
		printStringToConsole("<font color=green>Executing script from Editor...</font>"
				     "<font color=silver> </font>");
		QScriptValue result = engine->evaluate(code);
		if (engine->hasUncaughtException())
		{
			printErrorToConsole(result, true);
		} else {
			printStringToConsole("<font color=green>Complete</font>"
					     "<font color=silver> </font>");
		}
		newScriptingLine();
	}
}


void ScriptingConsole::setCompleter(QCompleter *newCompleter)
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


void ScriptingConsole::keyPressEvent(QKeyEvent *e)
{
	// Keyboard input should only work on the active line
	if (textCursor().blockNumber() == document()->blockCount()-1 &&
	    textCursor().positionInBlock() > lineHeader.length()-1)
	{
		if (e->key() == Qt::Key_Backspace)
		{
			// Make sure we can't backspace past the console arrows
			// or at all if we aren't on the lowest line
			if (lineUnderCursor().length() > lineHeader.length() &&
			    textCursor().blockNumber() == document()->blockCount()-1)
				QTextEdit::keyPressEvent(e);

		}
		else if (e->key() == Qt::Key_Up)
		{
			// Load scripting history
			e->ignore();
		}
		else if (e->key() == Qt::Key_Down)
		{
			// Load scripting history
			e->ignore();
		}
		else if (e->key() == Qt::Key_Left)
		{
			// Don't let the user go past the console arrows
			if (textCursor().positionInBlock() > lineHeader.length())
				QTextEdit::keyPressEvent(e);
		}
		else if (e->key() == Qt::Key_Home)
		{
			QTextCursor cursor = textCursor();
			cursor.movePosition(QTextCursor::StartOfBlock);
			cursor.movePosition(QTextCursor::Right, QTextCursor::MoveAnchor, lineHeader.length());
			setTextCursor(cursor);

		}
		else if (e->key() == Qt::Key_Enter || e->key() == Qt::Key_Return)
		{
			if (completer && completer->popup()->isVisible())
			{
				// If the completer is open, ignore
				e->ignore();
			} else {
				// Otherwise run the script on the current line
				executeCurrentLine();
			}
		}
		else
		{
			bool isShortcut = ((e->modifiers() & Qt::ControlModifier) && e->key() == Qt::Key_Space);

			if (!completer || !isShortcut)
				QTextEdit::keyPressEvent(e);

			const bool ctrlOrShift = e->modifiers() & (Qt::ControlModifier | Qt::ShiftModifier);
			if (!completer || (ctrlOrShift && e->text().isEmpty()))
				return;
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
	} else {
		e->ignore();
	}
}


void ScriptingConsole::executeCurrentLine()
{
	QString currLine = lineUnderCursor();
	currLine.remove(0, lineHeader.length());
	if (engine)
	{
		QScriptValue result = engine->evaluate(currLine);
		if (engine->hasUncaughtException())
			printErrorToConsole(result, false);
		else
			printToConsole(result);
		newScriptingLine();
	}
}


void ScriptingConsole::initializeScriptingEngine()
{
	// Redirect output to the console
	QScriptValue printFunction = engine->newFunction(&printToConsole_static);
	engine->globalObject().setProperty("print", printFunction);

	QScriptValue console = engine->newQObject(this);
	engine->globalObject().setProperty("_consolePtr", console);
}


QString ScriptingConsole::lineUnderCursor()
{
	QTextCursor cursor = textCursor();
	cursor.select(QTextCursor::LineUnderCursor);
	return cursor.selectedText();
}


void ScriptingConsole::newScriptingLine()
{
	moveCursor(QTextCursor::End);
	insertPlainText("\n");
	insertPlainText(lineHeader);
	moveCursor(QTextCursor::End);
}


void ScriptingConsole::printErrorToConsole(QScriptValue result, bool includeLineNumber)
{
	insertPlainText("\n");
	if (includeLineNumber)
		insertHtml("<font color=red>Error (Line " +
			   QString::number(engine->uncaughtExceptionLineNumber()) + "): ");
	else
		insertHtml("<font color=red>Error: ");
	insertHtml(result.toString());
	insertHtml("</font><font color=silver> </font>");
}


void ScriptingConsole::printStringToConsole(QString string)
{
	insertPlainText("\n");
	insertHtml(string);
}


void ScriptingConsole::printValueToConsole(QScriptValue value)
{
	if (value.isFunction())
		return;

	insertPlainText("\n");
	if (value.isString())
		insertPlainText(value.toString());
	else if (value.isNumber())
		insertPlainText(QString::number(value.toNumber()));
}


QString ScriptingConsole::textUnderCursor() const
{
	QTextCursor cursor = textCursor();
	cursor.select(QTextCursor::LineUnderCursor);
	return cursor.selectedText().split(QRegularExpression("\\(|\\s|\\n|\u2029")).last();
}


void ScriptingConsole::insertCompletion(const QString &completion)
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


void ScriptingConsole::printToConsole(QScriptValue value)
{
	if (value.isFunction())
		return;
	moveCursor(QTextCursor::End);
	printValueToConsole(value);
}


void ScriptingConsole::printToConsole(QScriptContext *context)
{
	moveCursor(QTextCursor::End);
	if (context)
	{
		for (int i=0; i<context->argumentCount(); ++i)
			printValueToConsole(context->argument(i));
	}
}
