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
    GerenciadorDocumento.cpp \
    EditorCodigo.cpp \
    Documento.cpp \
    AreaNumero.cpp

HEADERS  += ide.h \
    GerenciadorDocumento.h \
    Documento.h \
    EditorCodigo.h \
    AreaNumero.h

FORMS    += ide.ui

RESOURCES += \
    resource.qrc
