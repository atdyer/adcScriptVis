#ifndef SCRIPTINGCONSOLE_H
#define SCRIPTINGCONSOLE_H

#include <QTextEdit>
#include <QKeyEvent>
#include <QCompleter>
#include <QScriptEngine>
#include <QAbstractItemView>
#include <QScrollBar>
#include <QRegularExpression>
#include <QDebug>

#include "Scripting/ScriptingFunctions.h"

class ScriptingConsole : public QTextEdit
{
		Q_OBJECT
	public:
		explicit	ScriptingConsole(QWidget *parent = 0);

		void		addScriptableObject(QObject *newObject);
		void		executeCode(QString code);
		void		setCompleter(QCompleter *newCompleter);

	protected:

		void	keyPressEvent(QKeyEvent *e);

	private:

		QCompleter	*completer;
		QScriptEngine	*engine;
		QString		lineHeader;

		void	executeCurrentLine();
		void	initializeScriptingEngine();
		QString	lineUnderCursor();
		void	newScriptingLine();
		void	printErrorToConsole(QScriptValue result, bool includeLineNumber);
		void	printStringToConsole(QString string);
		void	printValueToConsole(QScriptValue value);
		QString	textUnderCursor() const;

	private slots:

		void	insertCompletion(const QString &completion);

	public slots:

		void	printToConsole(QScriptValue value);
		void	printToConsole(QScriptContext *context);

};

inline static QScriptValue printToConsole_static(QScriptContext *context, QScriptEngine *engine)
{
	// Find the stored console pointer
	QScriptValue globalEngine = engine->globalObject();
	QScriptValue consoleVal = globalEngine.property("_consolePtr");
	if (consoleVal.isValid() && consoleVal.isQObject())
	{
		QObject *consolePtr = consoleVal.toQObject();
		ScriptingConsole *console = qobject_cast<ScriptingConsole*>(consolePtr);
		if (console)
		{
			console->printToConsole(context);
			return context->callee();
		}
	}

	// Fall back on standard output
	for (int i=0; i<context->argumentCount(); ++i)
		std::cout << context->argument(i).toString().toStdString() << std::endl;
	return context->callee();
}

#endif // SCRIPTINGCONSOLE_H
