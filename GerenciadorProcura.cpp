#include "GerenciadorProcura.h"

GerenciadorProcura::GerenciadorProcura(QObject *parent) :
    QObject(parent)
{
    visivel = false;
    substituir = false;
}

GerenciadorProcura::~GerenciadorProcura()
{
    if(visivel)
    {
        delete widget;
    }
}

bool GerenciadorProcura::isVisivel()
{
    return this->visivel;
}

void GerenciadorProcura::setVisivel(bool visivel)
{
    this->visivel = visivel;
}

QWidget *GerenciadorProcura::getWidget()
{
    return this->widget;
}

QPushButton *GerenciadorProcura::getBotaoFechar()
{
    return this->botaoFechar;
}

void GerenciadorProcura::atualizarEditor()
{

}

void GerenciadorProcura::mostrar()
{
    if(!visivel)
    {

        this->widget = criarAba();
        visivel = true;
    }
}

void GerenciadorProcura::setTabWidget(QTabWidget *tabWidget)
{
    this->tabWidget = tabWidget;
}

void GerenciadorProcura::setEditor(QPlainTextEdit *edit)
{
    this->edit = edit;
}

void GerenciadorProcura::localizarProximo()
{

}

void GerenciadorProcura::localizarAnterior()
{

}

void GerenciadorProcura::setSubstituir(bool substituir)
{
    this->substituir = substituir;
    atualizarInterface();
}

void GerenciadorProcura::atualizarInterface()
{
    setTituloAba(getTituloAba());
}

QPushButton *GerenciadorProcura::criarBotaoFecharAba(QWidget* pai)
{
    //Cria um botao
    QPushButton *button = new QPushButton(pai);

    //Seta o Icon do botão
    button->setIcon(*(new QIcon(":/fechar.png")));

    //Seta o tamanho maximo
    button->setFixedWidth(20);
    button->setFixedHeight(20);

    //Conecta o sinal para receber quando este for clicado
    connect(button,SIGNAL(clicked()),this,SLOT(esconder()));

    return button;
}

QWidget *GerenciadorProcura::criarAba()
{
    //Criar a aba..
    QWidget* tab = new QWidget();

    //Inseri a aba...
    int id = tabWidget->addTab(tab, getTituloAba());

    //seta a nova aba como atual
    tabWidget->setCurrentWidget(tab);

    //Criar botao fechar
    this->botaoFechar = criarBotaoFecharAba(tab);

    //Inseri o botao
    tabWidget->tabBar()->setTabButton(id, QTabBar::RightSide, (QWidget*) (botaoFechar));

    return tab;
}

QString GerenciadorProcura::getTituloAba()
{
    if(substituir)
    {
        return "Localizar e Substituir";
    }

    return "Localizar";
}

void GerenciadorProcura::setTituloAba(QString titulo)
{
    tabWidget->setTabText(indiceAba(), titulo);
}

int GerenciadorProcura::indiceAba()
{
    return tabWidget->indexOf(widget);
}

void GerenciadorProcura::mudouEditor(QPlainTextEdit *edit)
{
    this->edit = edit;
}

void GerenciadorProcura::esconder()
{
    if(visivel)
    {
        visivel = false;
        delete widget;
    }
}
