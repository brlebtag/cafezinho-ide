#include "ide.h"
#include "ui_ide.h"

IDE::IDE(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::IDE)
{
    ui->setupUi(this);

    connect(this->ui->actionAbrir,SIGNAL(triggered()),this,SLOT(actionAbrirClicked()));
    connect(this->ui->actionNovo,SIGNAL(triggered(bool)),this,SLOT(actionNovoClicked(bool)));
    connect(this->ui->actionFechar,SIGNAL(triggered(bool)),this,SLOT(actionFecharClicked(bool)));
    connect(this->ui->actionSair,SIGNAL(triggered(bool)),this,SLOT(actionSairClicked(bool)));
    connect(this->ui->actionSalvar,SIGNAL(triggered(bool)),this,SLOT(actionSalvarClicked(bool)));
    connect(this->ui->actionSalvar_Como,SIGNAL(triggered(bool)),this,SLOT(actionSalvarComoClicked(bool)));

    //Index da aba atual...
    int index = this->ui->tabWidgetArquivos->currentIndex();

    //Cria um QPlainTextEdit e inseri na tab
    QPlainTextEdit *edit = new QPlainTextEdit(this->ui->tabWidgetArquivos->currentWidget());

    //adiciona o connect para salvar as mudanças no texto...
    connect(edit,SIGNAL(textChanged()),this,SLOT(plainTextEditTextChanged()));

    //configura a politica de tamanho
    edit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    //Cria um layout
    QVBoxLayout * layout = new QVBoxLayout();

    //Inseri o TextEdit no layout
    layout->addWidget(edit);

    //Inseri o layout na tab
    this->ui->tabWidgetArquivos->currentWidget()->setLayout(layout);

    //Cria um conteiner para guardar informações sobre o documento
    Document* doc = new Document(index,edit);

    //inseri a tab na Hashtable
    arquivos.insert(index,doc);

    //Ajusta o ultimo caminho
    lastPath = QDir::currentPath();
}

IDE::~IDE()
{
    //deleta o HashTable
    delete ui;
}

void IDE::actionAbrirClicked(bool checked)
{

    //Abrir a janela pedindo ao usuario que entre com o arquivo...
    QString fileName = QFileDialog::getOpenFileName(this, tr("Abrir Arquivo"), lastPath, tr("Files (*.cafe)"));

    if(fileName.isEmpty())
        return;

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

    //Verifica se o editor já está com aquele arquivo aberto e senão o tiver aberto, ele o abre.
    if(!fileOpened.contains(QString(QCryptographicHash::hash(fileName.toUtf8(),QCryptographicHash::Md5).toHex())))
    {
        //pega o index do tab atual
        int index = this->ui->tabWidgetArquivos->currentIndex();

        //Pega o edit da hashtable
        Document* doc = arquivos.value(index);

        if(doc->isEmpty())
        {
            //Se o atual estiver vazio carrega o texto dentro dele...
            QString buffer = file.readAll();
            doc->setText(buffer);
            this->ui->tabWidgetArquivos->setTabText(index,QString(fileName.section(QDir::separator(),-1)));
            doc->setFileName(fileName);
            lastPath = fileName.remove(fileName.section(QDir::separator(),-1));//atualizo o ultimo arquivo
            fileOpened.insert(doc->getFileId());
        }
        else
        {

            //Criar a aba..
            QWidget* tab = new QWidget(this->ui->tabWidgetArquivos);

            //Configura o toolTip para mostrar o caminho completo do arquivo
            tab->setToolTip(fileName);

            //Inseri a aba no tabWidget o titulo é apenas a ultima parte do caminho full do arquivo (só o nome do arquivo)
            int index = this->ui->tabWidgetArquivos->addTab(tab,fileName.section(QDir::separator(),-1));

            //seta a nova aba como atual
            this->ui->tabWidgetArquivos->setCurrentWidget(tab);

            //Cria um QPlainTextEdit e inseri na nova tab
            QPlainTextEdit *edit = new QPlainTextEdit(tab);

            //adiciona o connect para salvar as mudanças no texto...
            connect(edit,SIGNAL(textChanged()),this,SLOT(plainTextEditTextChanged()));

            //configura a politica de tamanho
            edit->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);

            //Cria um layout
            QVBoxLayout * layout = new QVBoxLayout();

            //Inseri o TextEdit no layout
            layout->addWidget(edit);

            //Inseri o layout na tab
            tab->setLayout(layout);

            //Cria um conteiner para guardar informações sobre o documento aberto
            Document* doc = new Document(fileName,index,edit);

            //inseri a tab na Hashtable
            arquivos.insert(index,doc);

            //Inseri no hashtable de arquivos abertos
            fileOpened.insert(doc->getFileId());

            //Coloca o texto do arquivo no PlainTextEdit
            edit->appendPlainText(file.readAll());
        }
    }

    //Fecha o arquivo...
    file.close();
}

void IDE::actionNovoClicked(bool checked)
{
    //Criar a aba..
    QWidget* tab = new QWidget(this->ui->tabWidgetArquivos);

    //Inseri a aba no tabWidget
    int index = this->ui->tabWidgetArquivos->addTab(tab,QString(tr("Novo Arquivo*")));

    //seta a nova aba como atual
    this->ui->tabWidgetArquivos->setCurrentWidget(tab);

    //Cria um QPlainTextEdit e inseri na nova tab
    QPlainTextEdit *edit = new QPlainTextEdit(tab);

    //adiciona o connect para salvar as mudanças no texto...
    connect(edit,SIGNAL(textChanged()),this,SLOT(plainTextEditTextChanged()));

    //configura a politica de tamanho
    edit->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);

    //Cria um layout
    QVBoxLayout * layout = new QVBoxLayout();

    //Inseri o TextEdit no layout
    layout->addWidget(edit);

    //Inseri o layout na tab
    tab->setLayout(layout);

    Document *doc = new Document(index,edit);

    //inseri a tab na Hashtable
    arquivos.insert(index, doc);
}

void IDE::actionFecharClicked(bool checked)
{
    //pega o index do tab atual
    int index = this->ui->tabWidgetArquivos->currentIndex();

    //Pega o edit da hashtable
    Document* doc = arquivos.value(index);

    //Verifica se existe mais de uma aba...
    if(arquivos.size()>1)
    {
        if(doc->isDirty())
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

                QString path;

                if(doc->isOpened())
                    path = doc->getPath();
                else
                    path = lastPath;
                //A onde salvar
                QString fileName = QFileDialog::getSaveFileName(
                                                                    this,
                                                                    tr("Salvar Arquivo"),
                                                                    path,
                                                                    tr("Arquivo Cafezinho(*.cafe)"),
                                                                    new QString(tr("Arquivo Cafezinho (*.cafe)"))
                                                                );

                //Se estiver vazia não fecha a aba...
                if(fileName.isEmpty())
                    return;

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
                out<<doc->getText();

            }
            else if(result == QMessageBox::Cancel)
            {
                return;
            }
        }

        //remove o tab
        this->ui->tabWidgetArquivos->removeTab(index);

        //remove o tab da hash
        arquivos.remove(index);

        //remove o arquivo da tabela de aberto: se não estava aberto não acontece nada.
        fileOpened.remove(doc->getFileId());

        //Deleta o container do documento...
        delete doc;
    }

    //se existir apenas essa aba não a fecha e tbm não aparece janela de salva (apenas não fecha)...
}

void IDE::actionSairClicked(bool checked)
{


}

void IDE::actionSalvarClicked(bool checked)
{
    //pega o index do tab atual
    int index = this->ui->tabWidgetArquivos->currentIndex();

    //Pega o edit da hashtable
    Document* doc = arquivos.value(index);

    QString fileName;
    bool salvar_como = false;

    if(!doc->isOpened())
    {
        //mostra a tela de aberto

        //A onde salvar
        fileName = QFileDialog::getSaveFileName(
                                                    this,
                                                    tr("Salvar Arquivo"),
                                                    lastPath,
                                                    tr("Arquivo Cafezinho(*.cafe)"),
                                                    new QString(tr("Arquivo Cafezinho (*.cafe)"))
                                                );
        //Se estiver vazia não salva nada...
        if(fileName.isEmpty())
            return;

        salvar_como = true;

    }
    else
    {
        fileName = doc->getPath();
    }

    //apenas salva o arquivo
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

    //Se foi salvar como então o arquivo possivelmente mudou de local e agora estamos trabalhando naquele local...
    if(salvar_como)
    {
        //remove o antigo file...
        fileOpened.remove(doc->getFileId());

        doc->setFileName(fileName);

        //Reinsere o novo...
        fileOpened.insert(doc->getFileId());

    }

    //Grava arquivo no disco...
    QTextStream out(&file);
    out<<doc->getText();

    //Marca o arquivo como limpo...
    doc->gotCleaned();

    //Seta ou reseta o nome da aba
    this->ui->tabWidgetArquivos->setTabText(index, fileName.section(QDir::separator(),-1));

    //Fecha o arquivo
    file.close();

}

void IDE::actionSalvarComoClicked(bool checked)
{
    //pega o index do tab atual
    int index = this->ui->tabWidgetArquivos->currentIndex();

    //Pega o edit da hashtable
    Document* doc = arquivos.value(index);

    //A onde salvar
    QString fileName = QFileDialog::getSaveFileName(
                                                this,
                                                tr("Salvar Arquivo"),
                                                lastPath,
                                                tr("Arquivo Cafezinho(*.cafe)"),
                                                new QString(tr("Arquivo Cafezinho (*.cafe)"))
                                            );
    //Se estiver vazia não salva nada...
    if(fileName.isEmpty())
        return;

    //apenas salva o arquivo
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

    //remove o antigo file...
    fileOpened.remove(doc->getFileId());

    doc->setFileName(fileName);

    //Reinsere o novo...
    fileOpened.insert(doc->getFileId());

    //Grava arquivo no disco...
    QTextStream out(&file);
    out<<doc->getText();

    //Marca o arquivo como limpo...
    doc->gotCleaned();

    //Seta ou reseta o nome da aba
    this->ui->tabWidgetArquivos->setTabText(index, fileName.section(QDir::separator(),-1));

    //Fecha o arquivo
    file.close();
}

void IDE::plainTextEditTextChanged()
{

    //pega o index do tab atual
    int index = this->ui->tabWidgetArquivos->currentIndex();

    //Pega o edit da hashtable
    Document* doc = arquivos.value(index);
    if(doc->isDirty()&&(doc->isOpened()))
    {

        //poem o texto no lugar
        QString text =doc->getPath().section(QDir::separator(),-1);
        text+="*";
        this->ui->tabWidgetArquivos->setTabText(index, text);
    }

    if(doc->isEmpty()&&(!doc->isOpened()))
        doc->gotCleaned(); //Marca o documento como limpo por que está vazio.
    else
        doc->gotDirty(); //Marca o documento como sujo por que não ta vazio e foi alterado algo
}
