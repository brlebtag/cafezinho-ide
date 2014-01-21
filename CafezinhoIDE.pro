#-------------------------------------------------
#
# Project created by QtCreator 2014-01-18T09:53:14
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CafezinhoIDE
TEMPLATE = app


SOURCES += main.cpp\
        ide.cpp \
    document.cpp \
    codeeditor.cpp \
    linenumberarea.cpp

HEADERS  += ide.h \
    document.h \
    codeeditor.h \
    linenumberarea.h

FORMS    += ide.ui
