#include "ide.h"
#include "ui_ide.h"

IDE::IDE(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::IDE)
{
    ui->setupUi(this);
}

IDE::~IDE()
{
    delete ui;
}
