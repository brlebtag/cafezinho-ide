#include "GerenciadorMenuReabrir.h"

/*
 *  --- Configuração do Menu --
 *
 *  QList [ "mais recente" -> .... -> "mais antigo" ] portanto novos menus são inserido no começo (prepend) e
 *  os antigos são removidos do fim ( pop_back() )
 *
 *  Eu simplesmente insiro no acoesSubMenu e reabrirMenu e posteriormente atualizo o texto dos menus...
 *
 */

const int GerenciadorMenuReabrir::NUM_MENU_REABRIR = 5;

GerenciadorMenuReabrir::GerenciadorMenuReabrir(QObject *parent) :
    QObject(parent), configuracoes(QSettings::IniFormat, QSettings::UserScope, "UFG", "CafezinhoIDE")
{
    //Carregar o menu salvo...
    //Pega a quantidade de menus reabrir e marca o inicio do array...
    int size = configuracoes.beginReadArray("reabrir_menu");

    QString caminho;

    for(int i=0; i<size&&i<GerenciadorMenuReabrir::NUM_MENU_REABRIR; ++i)
    {
        //seta o index no array
        configuracoes.setArrayIndex(i);
        //pega o valor caminho
        caminho = configuracoes.value("caminho").toString();
        //criar um par <caminhoDocumento,documentoId> e inseri no documentos...
        caminhos.append(caminho);
    }

    //marca como fim do array...
    configuracoes.endArray();

    for(int i=0; i<caminhos.size(); ++i)
    {
        //Cria o submenu
        QAction *action = new QAction(&reabrirMenu);
        //conectando para receber o sinal que o submenu foi clicado
        connect(action, SIGNAL(triggered(bool)), this, SLOT(clicouAcoes()));
        //Inseri o submenu na lista de submenus
        acoesSubMenu.append(action);
        //Inseri os submenus no menu Reabrir
        reabrirMenu.addAction(action);
        //seta o texto do submenu
        action->setText(QString::number(i+1)+". "+caminhos[i]);
    }
}

GerenciadorMenuReabrir::~GerenciadorMenuReabrir()
{
    //Gravar o menu no disco...
    configuracoes.beginWriteArray("reabrir_menu");
    for (int i = 0; i < caminhos.size(); ++i)
    {
         configuracoes.setArrayIndex(i);
         configuracoes.setValue("caminho", caminhos[i]);
    }
    configuracoes.endArray();
}

void GerenciadorMenuReabrir::atualizar(QString &caminho)
{
    //Atualizo a lista do menu, se este não existir insiro ele
    //senao só troco as posicoes
    int pos = caminhos.indexOf(caminho);

    //Se o caminho não existe ainda...
    if(pos == -1)
    {
        //Se existe menos menu que o maximo...
        if(caminhos.size()<GerenciadorMenuReabrir::NUM_MENU_REABRIR)
        {
            //Cria o submenu
            QAction *action = new QAction(&reabrirMenu);
            //conectando para receber o sinal que o submenu foi clicado
            connect(action, SIGNAL(triggered()), this, SLOT(clicouAcoes()));
            //Inseri o submenu na lista de submenus
            acoesSubMenu.append(action);
            //Inseri os submenus no menu Reabrir
            reabrirMenu.addAction(action);
        }
        else
        {
            caminhos.pop_back();
        }
    }
    else
    {
        caminhos.removeAt(pos);
    }

    //adiciona no começo do QList
    caminhos.prepend(caminho);

    //reinicia o texto dos menus...
    resetarMenu();
}

QString GerenciadorMenuReabrir::getCaminhoSubMenu(QObject *emissor)
{
    int i = 0;
    for(QList<QAction*>::iterator it = acoesSubMenu.begin(); it != acoesSubMenu.end(); ++it, ++i)
    {
        QAction* action = (*it);
        if(action == emissor)
        {
            return caminhos[i];
        }
    }
    return "";
}

QMenu *GerenciadorMenuReabrir::getMenu()
{
    return &(this->reabrirMenu);
}

int GerenciadorMenuReabrir::tamanho()
{
    return this->acoesSubMenu.size();
}

void GerenciadorMenuReabrir::resetarMenu()
{
    int i = 0;
    for(QList<QAction*>::iterator it = acoesSubMenu.begin(); it != acoesSubMenu.end(); ++it, ++i)
    {
        QAction* action = (*it);
        action->setText(QString::number(i+1)+". "+caminhos[i]);
    }
}

void GerenciadorMenuReabrir::clicouAcoes()
{
    QString caminho = getCaminhoSubMenu(QObject::sender());
    emit menuReabrirClicou(caminho);
}
