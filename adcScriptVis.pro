#-------------------------------------------------
#
# Project created by QtCreator 2014-05-14T12:18:21
#
#-------------------------------------------------

QT       += core gui opengl script

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = adcScriptVis
TEMPLATE = app

DEFINES += GLEW_STATIC

SOURCES += main.cpp\
        MainWindow.cpp \
    Scripting/ScriptingWidget.cpp \
    Scripting/ScriptingTextEdit.cpp \
    OpenGL/OpenGLWidget.cpp \
    Widgets/Navigator/FileSystemViewer.cpp \
    Adcirc/Fort14.cpp \
    Scripting/ScriptingCompleter.cpp \
    Scripting/ScriptingConsole.cpp \
    Adcirc/IO/Fort14IO.cpp \
    Adcirc/Data/Node.cpp \
    Adcirc/Data/Element.cpp \
    OpenGL/Shaders/GLShader.cpp \
    OpenGL/Cameras/GLCamera.cpp \
    Layers/Layer.cpp \
    Layers/LayerStack.cpp \
    OpenGL/Cameras/GLCamera2D.cpp \
    Layers/MeshLayer.cpp \
    OpenGL/GLEW/glew.c \
    OpenGL/Shaders/SolidShader.cpp \
    OpenGL/Shaders/GradientShader.cpp \
    OpenGL/Cameras/GLCamera3D.cpp \
    Adcirc/Fort63.cpp \
    Adcirc/IO/Fort63IO.cpp

HEADERS  += MainWindow.h \
    Scripting/ScriptingWidget.h \
    Scripting/ScriptingTextEdit.h \
    OpenGL/OpenGLWidget.h \
    Widgets/Navigator/FileSystemViewer.h \
    Adcirc/Fort14.h \
    Scripting/ScriptingCompleter.h \
    Scripting/ScriptingFunctions.h \
    Scripting/ScriptingConsole.h \
    Adcirc/IO/Fort14IO.h \
    Adcirc/Data/Node.h \
    Adcirc/Data/AdcircData.h \
    Adcirc/Data/Element.h \
    OpenGL/Shaders/GLShader.h \
    OpenGL/OpenGLData.h \
    OpenGL/Cameras/GLCamera.h \
    Layers/Layer.h \
    Layers/LayerStack.h \
    OpenGL/Cameras/GLCamera2D.h \
    Layers/MeshLayer.h \
    OpenGL/GLEW/glew.h \
    OpenGL/GLEW/glxew.h \
    OpenGL/GLEW/wglew.h \
    OpenGL/Shaders/SolidShader.h \
    OpenGL/Shaders/GradientShader.h \
    OpenGL/Cameras/GLCamera3D.h \
    Adcirc/Fort63.h \
    Adcirc/IO/Fort63IO.h

FORMS    += MainWindow.ui \
    Scripting/ScriptingWidget.ui

RESOURCES += \
    qdarkstyle/style.qrc \
    images/icons.qrc
