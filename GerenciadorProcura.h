#ifndef GERENCIADORPROCURA_H
#define GERENCIADORPROCURA_H

#include <QObject>
#include <QWidget>
#include <QPushButton>
#include <QPlainTextEdit>
#include <QTabWidget>
#include <QTabBar>
#include <QTextDocument>
#include <QTextCursor>
#include <QColor>
#include <QTextEdit>
#include <QList>
#include <QTextBlock>
#include <QTextFormat>
#include "procurar.h"
#include <QDebug>
#include "Documento.h"


class IDE;

class GerenciadorProcura : public QObject
{
    Q_OBJECT
public:
    explicit GerenciadorProcura(IDE *ide, QObject *parent = 0);
    virtual ~GerenciadorProcura();
    bool isVisivel();
    void setVisivel(bool visivel);
    QWidget* getWidget();
    QPushButton *getBotaoFechar();
    void mostrar();
    void setTabWidget(QTabWidget* tabWidget);
    void setEditorProcurar(QPlainTextEdit *edit);
    void setSubstituir(bool substituir);
    void atualizarInterface();
    bool isPalavraProcuradaVazia();

private:
    QTabWidget *tabWidget;
    Procurar *widget;
    QPushButton *botaoFechar;
    IDE *ide;
    bool visivel;
    bool substituir;
    QString palavraProcurada;
    QString palavraSubstituir;
    QPushButton* criarBotaoFecharAba(QWidget *pai);
    Procurar *criarAba();
    QString getTituloAba();
    void setTituloAba(QString titulo);
    int indiceAba();
    bool palavraInteira;
    bool ignorarMaisculo;

signals:

public slots:
    void esconder();
    void localizar();
    void localizarAnterior();

private slots:
    void atualizarPalavraProcurada(QString palavra);
    void atualizarPalavraSubstituir(QString palavra);
    void substituirClicado();
    void substiturirTudoClicado();
    void ignorarMaisculoClicado(bool checked);
    void palavraInteiraClicado(bool checked);
    void mudouSelecao();

};

#endif // GERENCIADORPROCURA_H
