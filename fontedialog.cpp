#include "fontedialog.h"
#include "ui_fontedialog.h"

FonteDialog::FonteDialog(QString *fonte, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FonteDialog), fonte(fonte)
{
    ui->setupUi(this);

    QFontDatabase database;

    QStringList fontes = database.families();

    for(int i=0; i<fontes.size(); i++)
    {
        this->ui->listaFontes->addItem(fontes[i]);
        if(fontes[i] == *fonte)
            this->ui->listaFontes->setCurrentRow(i);
    }
    connect(this->ui->listaFontes,SIGNAL(currentTextChanged(QString)),this,SLOT(itemMudou(QString)));
}

FonteDialog::~FonteDialog()
{
    delete ui;
}

void FonteDialog::itemMudou(const QString & familia)
{
    (*fonte) = familia;
    this->ui->codigoExemplo->setFont(QFont(familia));
}
