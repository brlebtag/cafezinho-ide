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
    AreaNumeroLinha.cpp \
    GerenciadorMenuReabrir.cpp \
    fontedialog.cpp \
    irpara.cpp \
    GerenciadorProcura.cpp \
    procurar.cpp \
    Realcador.cpp \
    Documento.cpp \
    DadoBlocoTexto.cpp \
    MaquinaVirtual.cpp \
    Instrucao.cpp \
    CelulaMemoria.cpp \
    arvore_abstrata.cpp \
    CompInfo.cpp \
    CompThread.cpp \
    semantico.cpp \
    simbolo.cpp \
    checa_tipo.cpp \
    checa_vetor_dimensao.cpp \
    checa_chamada.cpp \
    nome.cpp

HEADERS  += ide.h \
    GerenciadorDocumento.h \
    EditorCodigo.h \
    AreaNumeroLinha.h \
    GerenciadorMenuReabrir.h \
    fontedialog.h \
    irpara.h \
    GerenciadorProcura.h \
    procurar.h \
    Realcador.h \
    Documento.h \
    DadoBlocoTexto.h \
    MaquinaVirtual.h \
    Instrucao.h \
    CelulaMemoria.h \
    arvore_abstrata.h \
    CompInfo.h \
    CompThread.h \
    semantico.h \
    simbolo.h

FORMS    += ide.ui \
    fontedialog.ui \
    irpara.ui \
    procurar.ui

RESOURCES += \
    resource.qrc

OTHER_FILES += \
    $$FLEXSOURCES \
    $$BISONSOURCES \
    lexer.l \
    parser.y

FLEXSOURCES = lexer.l
BISONSOURCES = parser.y

flexsource.input = FLEXSOURCES
flexsource.output = ${QMAKE_FILE_BASE}.cpp
flexsource.commands = flex --header-file=${QMAKE_FILE_BASE}.h -o ${QMAKE_FILE_BASE}.cpp ${QMAKE_FILE_IN}
flexsource.variable_out = SOURCES
flexsource.name = Flex Sources ${QMAKE_FILE_IN}
flexsource.CONFIG += target_predeps

QMAKE_EXTRA_COMPILERS += flexsource

flexheader.input = FLEXSOURCES
flexheader.output = ${QMAKE_FILE_BASE}.h
flexheader.commands = @true
flexheader.variable_out = HEADERS
flexheader.name = Flex Headers ${QMAKE_FILE_IN}
flexheader.CONFIG += target_predeps no_link

QMAKE_EXTRA_COMPILERS += flexheader

bisonsource.input = BISONSOURCES
bisonsource.output = ${QMAKE_FILE_BASE}.cpp
bisonsource.commands = bison -d --defines=${QMAKE_FILE_BASE}.h -o ${QMAKE_FILE_BASE}.cpp ${QMAKE_FILE_IN}
bisonsource.variable_out = SOURCES
bisonsource.name = Bison Sources ${QMAKE_FILE_IN}
bisonsource.CONFIG += target_predeps

QMAKE_EXTRA_COMPILERS += bisonsource

bisonheader.input = BISONSOURCES
bisonheader.output = ${QMAKE_FILE_BASE}.h
bisonheader.commands = @true
bisonheader.variable_out = HEADERS
bisonheader.name = Bison Headers ${QMAKE_FILE_IN}
bisonheader.CONFIG += target_predeps no_link

QMAKE_EXTRA_COMPILERS += bisonheader
