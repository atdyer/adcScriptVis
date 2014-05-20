#-------------------------------------------------
#
# Project created by QtCreator 2014-05-14T12:18:21
#
#-------------------------------------------------

QT       += core gui opengl script

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = adcScriptVis
TEMPLATE = app

LIBS += -lGLEW -lGLU -lGL

SOURCES += main.cpp\
        MainWindow.cpp \
    Scripting/ScriptingWidget.cpp \
    Scripting/ScriptingTextEdit.cpp \
    OpenGL/OpenGLWidget.cpp \
    Widgets/Navigator/FileSystemViewer.cpp \
    Adcirc/Fort14.cpp \
    Scripting/ScriptingCompleter.cpp \
    Scripting/ScriptingConsole.cpp

HEADERS  += MainWindow.h \
    Scripting/ScriptingWidget.h \
    Scripting/ScriptingTextEdit.h \
    OpenGL/OpenGLWidget.h \
    Widgets/Navigator/FileSystemViewer.h \
    Adcirc/Fort14.h \
    Scripting/ScriptingCompleter.h \
    Scripting/ScriptingFunctions.h \
    Scripting/ScriptingConsole.h

FORMS    += MainWindow.ui \
    Scripting/ScriptingWidget.ui

RESOURCES += \
    qdarkstyle/style.qrc \
    images/icons.qrc
