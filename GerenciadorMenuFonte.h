#ifndef GERENCIADORMENUFONTE_H
#define GERENCIADORMENUFONTE_H

#include <QObject>
#include <QMenu>
#include <QFontDatabase>
#include <QStringList>
#include <QAction>
#include <QActionGroup>

class GerenciadorMenuFonte : public QObject
{
    Q_OBJECT
public:
    explicit GerenciadorMenuFonte(QObject *parent = 0);
    QMenu* getMenu();
    void inicializar(QString fonte);

private:
    QMenu menuFonte;
    QActionGroup *actionFontes;

signals:
    void mudouFonte(QString fonte);
public slots:

private slots:
    void fonteClicado(QAction *action);

};

#endif // GERENCIADORMENUFONTE_H
