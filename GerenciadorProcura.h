#ifndef GERENCIADORPROCURA_H
#define GERENCIADORPROCURA_H

#include <QObject>
#include <QWidget>
#include <QPushButton>
#include <QPlainTextEdit>
#include <QDebug>
#include <QTabWidget>
#include <QTabBar>

class GerenciadorProcura : public QObject
{
    Q_OBJECT
public:
    explicit GerenciadorProcura(QObject *parent = 0);
    bool isVisivel();
    void setVisivel(bool visivel);
    QWidget* getWidget();
    QPushButton *getBotaoFechar();
    void atualizarEditor();

private:
    QTabWidget *tabWidget;
    QWidget *widget;
    QPushButton *botaoFechar;
    QPlainTextEdit *edit;
    bool visivel;
    QString palavraProcurada;

signals:

public slots:
    void mudouEditor(QPlainTextEdit * edit);
};

#endif // GERENCIADORPROCURA_H
