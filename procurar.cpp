#include "procurar.h"
#include "ui_procurar.h"

Procurar::Procurar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Procurar)
{
    ui->setupUi(this);
    setSubstituir(false);
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
