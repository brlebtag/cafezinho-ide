#ifndef GERENCIADORPROCURA_H
#define GERENCIADORPROCURA_H

#include <QObject>
#include <QWidget>
#include <QPushButton>
#include <QPlainTextEdit>
#include <QTabWidget>
#include <QTabBar>
#include "procurar.h"

class GerenciadorProcura : public QObject
{
    Q_OBJECT
public:
    explicit GerenciadorProcura(QObject *parent = 0);
    virtual ~GerenciadorProcura();
    bool isVisivel();
    void setVisivel(bool visivel);
    QWidget* getWidget();
    QPushButton *getBotaoFechar();
    void atualizarEditor();
    void mostrar();
    void setTabWidget(QTabWidget* tabWidget);
    void setEditor(QPlainTextEdit *edit);
    void localizarProximo();
    void localizarAnterior();
    void setSubstituir(bool substituir);
    void atualizarInterface();

private:
    QTabWidget *tabWidget;
    Procurar *widget;
    QPushButton *botaoFechar;
    QPlainTextEdit *edit;
    bool visivel;
    bool substituir;
    QString palavraProcurada;
    QPushButton* criarBotaoFecharAba(QWidget *pai);
    Procurar *criarAba();
    QString getTituloAba();
    void setTituloAba(QString titulo);
    int indiceAba();

signals:

public slots:
    void mudouEditor(QPlainTextEdit * edit);
    void esconder();
};

#endif // GERENCIADORPROCURA_H
