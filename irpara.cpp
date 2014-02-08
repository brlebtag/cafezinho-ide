#include "irpara.h"
#include "ui_irpara.h"

IrPara::IrPara(int maxSize, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::IrPara)
{
    ui->setupUi(this);
    QIntValidator *validator = new QIntValidator(1, maxSize, this);
    this->ui->editLinha->setValidator(validator);
    this->setFocus();
    this->ui->editLinha->setFocus();
}

IrPara::~IrPara()
{
    delete ui;
}

int IrPara::getNumeroLinha()
{
    return this->ui->editLinha->text().toInt();
}
        
