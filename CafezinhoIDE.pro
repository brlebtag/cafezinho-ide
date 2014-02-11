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
    AreaNumeroLinha.cpp \
    GerenciadorMenuReabrir.cpp \
    fontedialog.cpp \
    irpara.cpp \
    GerenciadorProcura.cpp \
    procurar.cpp

HEADERS  += ide.h \
    GerenciadorDocumento.h \
    Documento.h \
    EditorCodigo.h \
    AreaNumeroLinha.h \
    GerenciadorMenuReabrir.h \
    fontedialog.h \
    irpara.h \
    GerenciadorProcura.h \
    procurar.h

FORMS    += ide.ui \
    fontedialog.ui \
    irpara.ui \
    procurar.ui

RESOURCES += \
    resource.qrc
