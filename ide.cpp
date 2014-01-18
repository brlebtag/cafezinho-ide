#include "ide.h"
#include "ui_ide.h"

IDE::IDE(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::IDE)
{
    ui->setupUi(this);
    connect(this->ui->actionAbrir,SIGNAL(triggered()),this,SLOT(actionAbrirClicked()));
    //Criar a HashTable que irar guardar a informação se o arquivo já foi aberto no editor para não guardar novamente...
    fileOpened = new QHash<QFile,int>();
    this->num_arquivos_aberto = 0;
    this->num_arquivos_nao_salvo = 1;
    connect(this->ui->actionNovo,SIGNAL(triggered(bool)),this,SLOT(actionNovoClicked(bool)));
    connect(this->ui->actionFechar,SIGNAL(triggered(bool)),this,SLOT(actionFecharClicked(bool)));
    connect(this->ui->actionSair,SIGNAL(triggered(bool)),this,SLOT(actionSairClicked(bool)));
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

void IDE::actionNovoClicked(bool checked)
{
    //Incrementa o numero de arquivos não salvo
    this->num_arquivos_nao_salvo++;
    //Criar a aba..
    QWidget* tab = new QWidget(this->ui->tabWidgetArquivos);
    //Inseri a aba no tabWidget
    int index = this->ui->tabWidgetArquivos->addTab(tab,QString(tr("Novo Arquivo*")));
    //seta a nova aba como atual
    this->ui->tabWidgetArquivos->setCurrentWidget(tab);
    //Cria um QPlainTextEdit e inseri na nova tab
    QPlainTextEdit *edit = new QPlainTextEdit(tab);
    //configura a politica de tamanho
    edit->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    //Cria um layout
    QVBoxLayout * layout = new QVBoxLayout();
    //Inseri o TextEdit no layout
    layout->addWidget(edit);
    //Inseri o layout na tab
    tab->setLayout(layout);
    //inseri a tab na Hashtable
    arquivos.insert(index,edit);
}

void IDE::actionFecharClicked(bool checked)
{
    //pega o index do tab atual
    int index = this->ui->tabWidgetArquivos->currentIndex();
    //Pega o edit da hashtable
    QPlainTextEdit* edit = arquivos.value(index);

    //Verifica se existe mais de uma aba...
    if(this->num_arquivos_nao_salvo!=1)
    {
        if(!edit->toPlainText().isEmpty())
        {
            //Perqunta se pode fechar assim mesmo
            int result = QMessageBox::warning(
                                                this,tr("CafezinhoIDE"),
                                                tr("Deseja salvar as alterações antes de fechar?"),
                                                QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel,
                                                QMessageBox::Save
                                             );
            //deseja salvar...
            if(result == QMessageBox::Save)
            {
                //A onde salvar
                QString fileName = QFileDialog::getSaveFileName(
                                                                    this,
                                                                    tr("Salvar Arquivo"),
                                                                    QDir::currentPath(),
                                                                    tr("Arquivo Cafezinho(*.cafe)"),
                                                                    new QString(tr("Arquivo Cafezinho (*.cafe)"))
                                                                );
                //Abre o arquivo
                QFile file(fileName);

                //Verifica se é possivel gravar no arquivo...
                if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
                {
                    //Cria mensagem de erro...
                    QMessageBox msgBox;
                    msgBox.setWindowTitle("CafezinhoIDE");
                    msgBox.setText("Erro ao tentar salvar o arquivo");
                    msgBox.setInformativeText(file.errorString());
                    msgBox.setStandardButtons(QMessageBox::Ok);
                    msgBox.setDefaultButton(QMessageBox::Ok);
                    msgBox.exec();
                    //Sai e Não deleta a janela...
                    return;
                }
                //Grava arquivo no disco...
                QTextStream out(&file);
                out<<edit->toPlainText();
            }
        }
        //remove o tab
        this->ui->tabWidgetArquivos->removeTab(index);
        //remove o tab da hash
        arquivos.remove(index);
    }
    //se existir apenas essa aba não a fecha e tbm não aparece janela de salva (apenas não fecha)...
}

void IDE::actionSairClicked(bool checked)
{


}
