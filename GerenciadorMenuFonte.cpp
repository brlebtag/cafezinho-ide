#include "GerenciadorMenuFonte.h"

GerenciadorMenuFonte::GerenciadorMenuFonte(QObject *parent) :
    QObject(parent)
{

}

QMenu *GerenciadorMenuFonte::getMenu()
{
    return &(this->menuFonte);
}

void GerenciadorMenuFonte::inicializar(QString fonte)
{
    QFontDatabase database;

    QStringList fontes = database.families();

    //Cria um grupo para adicionar os actions... assim só um vai ficar ativo por vez...
    actionFontes = new QActionGroup(this);

    for(int i=0; i<fontes.size(); i++)
    {
        //Cria um Action
        QAction*action = new QAction(actionFontes);

        action->setText(fontes[i]);

        actionFontes->addAction(action);

        menuFonte.addAction(action);

        action->setCheckable(true);

        if(fontes[i] == fonte)
            action->setChecked(true);
    }

    connect(actionFontes,SIGNAL(triggered(QAction*)),this,SLOT(fonteClicado(QAction*)));
}

void GerenciadorMenuFonte::fonteClicado(QAction *action)
{
    QString fonte = action->text();
    emit mudouFonte(fonte);
}
