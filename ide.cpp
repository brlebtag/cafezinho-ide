#include "ide.h"
#include "ui_ide.h"

IDE::IDE(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::IDE)
{
    ui->setupUi(this);
    this->num_arquivo_abertos = 0;
    this->num_arquivo_nao_salvo = 1;
    connect(this->ui->actionAbrir,SIGNAL(triggered()),this,SLOT(actionAbrirClicked()));
    //Criar a HashTable que irar guardar a informação se o arquivo já foi aberto no editor para não guardar novamente...
    fileOpened = new QHash<QFile,int>();
}

IDE::~IDE()
{
    //deleta o HashTable
    delete fileOpened;
    delete ui;
}

void IDE::actionAbrirClicked(bool checked)
{

    //Abrir a janela pedindo ao usuario que entre com o arquivo...
    QString fileName = QFileDialog::getOpenFileName(this, tr("Abrir Arquivo"), "", tr("Files (*.cafe)"));
    //Abrir o arquivo...
    QFile file(fileName);
    //Verificar se o arquivo está aberto...
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        //Exibir mensagem de erro...
        QMessageBox msg;
        msg.setWindowTitle("Erro ao abrir o arquivo");
        msg.setText("Erro ao tentar abrir o arquivo ");
        msg.setInformativeText(file.errorString());
        msg.exec();
    }
    //Verifica se o editor já está com aquele arquivo aberto e senão o tiver aberto ele o abre.
    if(!fileOpened->contains(file))
    {
        //Verifica se só existe um arquivo não salvo
        if(this->num_arquivo_nao_salvo==1)
        {

        }
    }
    file.close();
}
