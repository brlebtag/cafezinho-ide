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
    CodeEditor *edit = new CodeEditor(this->ui->tabWidgetArquivos->currentWidget());

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

    //Cria um conteiner para guardar informações sobre o documento. O documento está limpo
    Document* doc = new Document(index,edit);

    //inseri a tab na Hashtable
    arquivos.insert(index,doc);

    //Ajusta o ultimo caminho
    lastPath = QDir::currentPath();

    //Coloca o Titulo
    this->ui->tabWidgetArquivos->setTabText(index, "Novo Arquivo");

    //Seta o foco no edit...
    edit->setFocus();
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
        Document* doc = arquivos.at(index);

        if(doc->isEmpty())
        {
            //Carrega o texto do arquivo para o buffer
            QString buffer = file.readAll();

            //Seta o documento sujo para não adicionar o * ... por que ao adicionar o texto lido do arquivo no PlainTextEdit
            //ele irá chamar textChanged mas nessa situação não queremos que adicione o * ...
            doc->gotDirty();

            //Poem o texto dentro do PlainTextEdit
            doc->setText(buffer);

            //agora marca o texto como limpo...
            doc->gotCleaned();

            //Seta o titulo da aba
            this->ui->tabWidgetArquivos->setTabText(index,QString(fileName.section(QDir::separator(),-1)));

            //Seta o nome do documento
            doc->setFileName(fileName);

            //Seta o documento como aberto
            doc->gotOpened();

            //Seta o toolTip da aba
            this->ui->tabWidgetArquivos->setTabToolTip(index, fileName);

            //Ajusta a variavel lastPath para o ultimo arquivo aberto
            lastPath = fileName.remove(fileName.section(QDir::separator(),-1));

            //Inseri o arquivo na tabela de arquivos abertos
            fileOpened.insert(doc->getFileId(), index);

            //seta focus no edit
            doc->setFocus();
        }
        else
        {

            //Criar a aba..
            QWidget* tab = new QWidget(this->ui->tabWidgetArquivos);

            //Inseri a aba no tabWidget o titulo é apenas a ultima parte do caminho full do arquivo (só o nome do arquivo)
            int index = this->ui->tabWidgetArquivos->addTab(tab,fileName.section(QDir::separator(),-1));

            //seta a nova aba como atual
            this->ui->tabWidgetArquivos->setCurrentWidget(tab);

            //Cria um QPlainTextEdit e inseri na nova tab
            CodeEditor *edit = new CodeEditor(tab);

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
            Document* doc = new Document(index,edit);

            //inseri a tab na Hashtable
            arquivos.insert(index, doc);

            //Seta o documento sujo para não adicionar o * ... por que ao adicionar o texto lido do arquivo no PlainTextEdit
            //ele irá chamar textChanged mas nessa situação não queremos que adicione o * ...
            doc->gotDirty();

            //Coloca o texto do arquivo no PlainTextEdit
            edit->appendPlainText(file.readAll());

            //agora marca o texto como limpo...
            doc->gotCleaned();

            //Seto o nome
            doc->setFileName(fileName);

            //Marca o arquivo como aberto
            doc->gotOpened();

            //Inseri no hashtable de arquivos abertos
            fileOpened.insert(doc->getFileId(), index);

            //Seta o toolTip como o caminho do arquivo
            this->ui->tabWidgetArquivos->setTabToolTip(index,fileName);

            //Seta o foco no edit...
            edit->setFocus();

        }
    }
    else
    {
        //Pega o index da aba que o documento está...
        int index_tab = fileOpened.value(QString(QCryptographicHash::hash(fileName.toUtf8(),QCryptographicHash::Md5).toHex()));

        //Seta a tab encontrada como atual...
        this->ui->tabWidgetArquivos->setCurrentIndex(index_tab);

        //Pega o documento e seta o focus
        Document * doc = arquivos.at(index_tab);

        //Seta o focus
        doc->setFocus();
    }

    //Fecha o arquivo...
    file.close();
}

void IDE::actionNovoClicked(bool checked)
{
    //Criar a aba..
    QWidget* tab = new QWidget(this->ui->tabWidgetArquivos);

    //Inseri a aba no tabWidget
    int index = this->ui->tabWidgetArquivos->addTab(tab,QString(tr("Novo Arquivo")));

    //seta a nova aba como atual
    this->ui->tabWidgetArquivos->setCurrentWidget(tab);

    //Cria um QPlainTextEdit e inseri na nova tab
    CodeEditor *edit = new CodeEditor(tab);

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

    //Seta o foco no edit...
    edit->setFocus();
}

void IDE::actionFecharClicked(bool checked)
{
    //pega o index do tab atual
    int index = this->ui->tabWidgetArquivos->currentIndex();

    //Pega o edit da hashtable
    Document* doc = arquivos.at(index);

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

            //Não quero sair...
            if(result == QMessageBox::Cancel)
                return;

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
        }

        //remove o tab
        this->ui->tabWidgetArquivos->removeTab(index);

        //remove o tab da hash
        arquivos.removeAt(index);

        //remove o arquivo da tabela de aberto: se não estava aberto não acontece nada.
        fileOpened.remove(doc->getFileId());

        //Deleta o container do documento...
        delete doc;
    }

    //se existir apenas essa aba não a fecha e tbm não aparece janela de salva (apenas não fecha)...
}

void IDE::actionSairClicked(bool checked)
{
    int index = 0;

    for(QList<Document*>::iterator it = arquivos.begin(); it!= arquivos.end(); it++, index++)
    {
        Document *doc = (*it);

        if(doc->isDirty())
        {


            //Seta a tab index como a atual...
            this->ui->tabWidgetArquivos->setCurrentIndex(index);

            //Seta o foco no edit...
            doc->setFocus();

            //Perqunta se pode fechar assim mesmo
            int result = QMessageBox::warning(
                                                this,tr("CafezinhoIDE"),
                                                tr("Deseja salvar as alterações antes de fechar?"),
                                                QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel,
                                                QMessageBox::Save
                                             );

            //Não quero sair...
            if(result == QMessageBox::Cancel)
                return;

            //deseja salvar...
            if(result == QMessageBox::Save)
            {

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

                //Adiciona a terminação .cafe se o usuario não informar
                if(!fileName.contains(".cafe"))
                {
                    fileName+=".cafe";
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

                //remove o antigo file...
                fileOpened.remove(doc->getFileId());

                doc->setFileName(fileName);

                //Reinsere o novo...
                fileOpened.insert(doc->getFileId(), index);

                //Grava arquivo no disco...
                QTextStream out(&file);
                out<<doc->getText();

                //Marca o arquivo como limpo...
                doc->gotCleaned();

                //Seta o toolTip como o caminho do arquivo
                this->ui->tabWidgetArquivos->setTabToolTip(index,fileName);

                //Seta ou reseta o nome da aba
                this->ui->tabWidgetArquivos->setTabText(index, fileName.section(QDir::separator(),-1));

                //Fecha o arquivo
                file.close();
            }

            //remove o tab
            this->ui->tabWidgetArquivos->removeTab(index);

            //remove o tab da hash
            arquivos.removeAt(index);

            //remove o arquivo da tabela de aberto: se não estava aberto não acontece nada.
            fileOpened.remove(doc->getFileId());

            //Deleta o container do documento...
            delete doc;
        }
    }

    qApp->exit(0);
}

void IDE::actionSalvarClicked(bool checked)
{
    //pega o index do tab atual
    int index = this->ui->tabWidgetArquivos->currentIndex();

    //Pega o edit da hashtable
    Document* doc = arquivos.at(index);

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

        //Adiciona a terminação .cafe se o usuario não informar
        if(!fileName.contains(".cafe"))
        {
            fileName+=".cafe";
        }

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
        fileOpened.insert(doc->getFileId(), index);

    }

    //Grava arquivo no disco...
    QTextStream out(&file);
    out<<doc->getText();

    //Marca o arquivo como limpo...
    doc->gotCleaned();

    //Seta o toolTip como o caminho do arquivo
    this->ui->tabWidgetArquivos->setTabToolTip(index,fileName);

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
    Document* doc = arquivos.at(index);

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

    //Adiciona a terminação .cafe se o usuario não informar
    if(!fileName.contains(".cafe"))
    {
        fileName+=".cafe";
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

    //remove o antigo file...
    fileOpened.remove(doc->getFileId());

    doc->setFileName(fileName);

    //Reinsere o novo...
    fileOpened.insert(doc->getFileId(), index);

    //Grava arquivo no disco...
    QTextStream out(&file);
    out<<doc->getText();

    //Marca o arquivo como limpo...
    doc->gotCleaned();

    //Seta o toolTip como o caminho do arquivo
    this->ui->tabWidgetArquivos->setTabToolTip(index,fileName);

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
    Document* doc = arquivos.at(index);

    if(!doc->isDirty())
    {

        //poem o texto no lugar
        QString text = this->ui->tabWidgetArquivos->tabText(index);
        text+="*";
        this->ui->tabWidgetArquivos->setTabText(index, text);
        doc->gotDirty();
    }
}
