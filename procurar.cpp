#include "procurar.h"
#include "ui_procurar.h"

Procurar::Procurar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Procurar)
{
    ui->setupUi(this);
    setSubstituir(false);
    connect(this->ui->botaoLocalizar,SIGNAL(clicked()),this,SLOT(localizar()));
    connect(this->ui->botaoSubstituir, SIGNAL(clicked()), this, SLOT(substitui()));
    connect(this->ui->botaoLocalizarAnterior, SIGNAL(clicked()), this, SLOT(localizarAnterior()));
    connect(this->ui->botaoSubstituirTudo, SIGNAL(clicked()), this, SLOT(substituirTudo()));
    connect(this->ui->botaoPalavraInteira_1, SIGNAL(clicked()), this, SLOT(palavraInteira()));
    connect(this->ui->botaoPalavraInteira_2, SIGNAL(clicked()), this, SLOT(palavraInteira()));
    connect(this->ui->botaoIgnorarMaiscula, SIGNAL(clicked()), this, SLOT(ignorarMaiscula()));
    connect(this->ui->editLocalizar,SIGNAL(editingFinished()), this, SLOT(palavraProcurada()));
    connect(this->ui->editSubstituir, SIGNAL(editingFinished()), this, SLOT(palavraSubstituir()));
}

Procurar::~Procurar()
{
    delete ui;
}

void Procurar::setSubstituir(bool substituir)
{
    this->substituir = substituir;
    atualizarInterface();
}

QString Procurar::getTextoLocalizar()
{
    return this->ui->editLocalizar->text();
}

QString Procurar::getTextoSubstituir()
{
    return this->ui->editSubstituir->text();
}

void Procurar::atualizarInterface()
{
    if(this->substituir)
    {
        //Esconde PalavraInteira_1
        this->ui->botaoPalavraInteira_1->hide();

        //Mostrar botao PalavraInteira_2
        this->ui->botaoPalavraInteira_2->show();

        //Se o botão 1 estava marcado então o 2 fica marcado tbm senão o contrario
        //( são 2 botões diferentes mas para o usuario é o mesmo)
        if(this->ui->botaoPalavraInteira_1->isChecked())
            this->ui->botaoPalavraInteira_2->setChecked(true);
        else
            this->ui->botaoPalavraInteira_2->setChecked(false);

        //Mostrar Label substituir
        this->ui->lblSubstituir->show();

        //Mostrar editSubstituir
        this->ui->editSubstituir->show();

        //Mostrar botao Substituir
        this->ui->botaoSubstituir->show();

        //Mostrar botao Substituir Tudo
        this->ui->botaoSubstituirTudo->show();

    }
    else
    {
        //Mostrar PalavraInteira_1
        this->ui->botaoPalavraInteira_1->show();

        //Esconde botao PalavraInteira_2
        this->ui->botaoPalavraInteira_2->hide();

        //Se o botão 1 estava marcado então o 2 fica marcado tbm senão o contrario
        //( são 2 botões diferentes mas para o usuario é o mesmo)
        if(this->ui->botaoPalavraInteira_2->isChecked())
            this->ui->botaoPalavraInteira_1->setChecked(true);
        else
            this->ui->botaoPalavraInteira_1->setChecked(false);

        //Esconder Label substituir
        this->ui->lblSubstituir->hide();

        //Esconder editSubstituir
        this->ui->editSubstituir->hide();

        //Esconde botao Substituir
        this->ui->botaoSubstituir->hide();

        //Esconde botao Substituir Tudo
        this->ui->botaoSubstituirTudo->hide();
    }
}

void Procurar::localizar()
{
    emit localizarClicado();
}

void Procurar::substitui()
{
    emit substituirClicado();
}

void Procurar::localizarAnterior()
{
    emit localizarAnteriorClicado();
}

void Procurar::substituirTudo()
{
    emit substituirTudoClicado();
}

void Procurar::ignorarMaiscula()
{
    emit ignorarMaisculaMarcado(this->ui->botaoIgnorarMaiscula->isChecked());
}

void Procurar::palavraInteira()
{
    if(QObject::sender()==this->ui->botaoPalavraInteira_1)
        emit palavraInteiraMarcado(this->ui->botaoPalavraInteira_1->isChecked());
    else
        emit palavraInteiraMarcado(this->ui->botaoPalavraInteira_2->isChecked());
}

void Procurar::palavraProcurada()
{
    emit mudouPalavraProcurada(this->ui->editLocalizar->text());
}

void Procurar::palavraSubstituir()
{
    emit mudouPalavraSubstituir(this->ui->editSubstituir->text());
}

