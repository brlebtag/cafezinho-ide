#include "irpara.h"
#include "ui_irpara.h"

IrPara::IrPara(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::IrPara)
{
    ui->setupUi(this);
    QIntValidator *validator = new QIntValidator(1, 2147483647, this);
    this->ui->editLinha->setValidator(validator);
}

IrPara::~IrPara()
{
    delete ui;
}

int IrPara::getNumeroLinha()
{
    return this->ui->editLinha->text().toInt();
}
        
