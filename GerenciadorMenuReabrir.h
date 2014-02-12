#ifndef GERENCIADORMENUREABRIR_H
#define GERENCIADORMENUREABRIR_H

#include <QObject>
#include <QList>
#include <QAction>
#include <QMenu>
#include <QSettings>
#include <QDir>

class GerenciadorMenuReabrir : public QObject
{
    Q_OBJECT
public:
    explicit GerenciadorMenuReabrir(QObject *parent = 0);
    virtual ~GerenciadorMenuReabrir();
    void atualizar(QString &caminho);
    QMenu* getMenu();
    const static int NUM_MENU_REABRIR;
    int tamanho();
    QString getUltimoCaminho();

private:
    QString getCaminhoSubMenu(QObject *emissor);
    void resetarMenu();
    QList<QString> caminhos;
    QList<QAction*> acoesSubMenu;
    QMenu reabrirMenu;
    QSettings configuracoes;

signals:
    void menuReabrirClicou(QString caminho);

public slots:

private slots:
    void clicouAcoes();

};

#endif // GERENCIADORMENUREABRIR_H
