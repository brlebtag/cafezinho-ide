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
    codeeditor.cpp \
    linenumberarea.cpp \
    documentmanager.cpp \
    documento.cpp

HEADERS  += ide.h \
    codeeditor.h \
    linenumberarea.h \
    documentmanager.h \
    documento.h

FORMS    += ide.ui

RESOURCES += \
    resource.qrc
