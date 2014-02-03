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
    connect(this->ui->actionNumero_da_Linha,SIGNAL(toggled(bool)),this,SLOT(actionNumero_da_linhaToggled(bool)));

    //Index da aba atual...
    int index = this->ui->tabWidgetArquivos->currentIndex();

    //Cria um QPlainTextEdit e inseri na tab
    CodeEditor *edit = new CodeEditor(this->ui->tabWidgetArquivos->currentWidget());

    //adiciona o connect para salvar as mudanças no texto...
    connect(edit,SIGNAL(textChanged()),this,SLOT(plainTextEditTextChanged()));

    //Para pegar os breakpoints
    connect(edit,SIGNAL(breakpoint(int,bool)),this,SLOT(breakpoint(int,bool)));

    //configura a politica de tamanho
    edit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    //Cria um layout
    QVBoxLayout * layout = new QVBoxLayout();

    //Inseri o TextEdit no layout
    layout->addWidget(edit);

    //Inseri o layout na tab
    this->ui->tabWidgetArquivos->currentWidget()->setLayout(layout);

    //Cria um conteiner para guardar informações sobre o documento. O documento está limpo
    Documento* doc = new Documento(this->ui->tabWidgetArquivos->currentWidget(), edit);

    //inseri a tab na Hashtable
    docMan.inserir(doc);

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

Documento *IDE::criarAba(QString title, int *index)
{
    //Criar a aba..
    QWidget* tab = new QWidget(this->ui->tabWidgetArquivos);

    //Inseri a aba no tabWidget o titulo é apenas a ultima parte do caminho full do arquivo (só o nome do arquivo)
    int id = this->ui->tabWidgetArquivos->addTab(tab, title);

    if(index != 0)
        (*index) = id;

    //seta a nova aba como atual
    this->ui->tabWidgetArquivos->setCurrentWidget(tab);

    //Cria um QPlainTextEdit e inseri na nova tab
    CodeEditor *edit = new CodeEditor(tab);

    //adiciona o connect para salvar as mudanças no texto...
    connect(edit,SIGNAL(textChanged()),this,SLOT(plainTextEditTextChanged()));

    //Para pegar os breakpoints
    connect(edit,SIGNAL(breakpoint(int,bool)),this,SLOT(breakpoint(int,bool)));

    //configura a politica de tamanho
    edit->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);

    //Cria um layout
    QVBoxLayout * layout = new QVBoxLayout();

    //Inseri o TextEdit no layout
    layout->addWidget(edit);

    //Inseri o layout na tab
    tab->setLayout(layout);

    //Cria um conteiner para guardar informações sobre o documento aberto
    Documento* doc = new Documento(tab, edit);

    return doc;
}

QString IDE::fileNameToFileId(QString &fileName)
{
    return QCryptographicHash::hash(fileName.toUtf8(),QCryptographicHash::Md5).toHex();
}

QString IDE::showAbrirArquivo()
{
    //Abrir a janela pedindo ao usuario que entre com o arquivo... e retorna a string
    showAbrirArquivo(lastPath);
}

QString IDE::showAbrirArquivo(QString &path)
{
    //Abrir a janela pedindo ao usuario que entre com o arquivo... e retorna a string
    return QFileDialog::getOpenFileName(this, tr("Abrir Arquivo"), path, tr("Files (*.cafe)"));
}

QString IDE::showSalvarArquivo()
{
    return showSalvarArquivo(lastPath);
}

QString IDE::showSalvarArquivo(QString path)
{
    return QFileDialog::getSaveFileName(this, tr("Salvar Arquivo"),path, tr("Arquivo Cafezinho(*.cafe)"), new QString(tr("Arquivo Cafezinho (*.cafe)")));
}

int IDE::showSalvarAlteracao()
{
    //Perqunta se pode fechar assim mesmo
    int result = QMessageBox::warning(
                                        this,tr("CafezinhoIDE"),
                                        tr("Deseja salvar as alterações antes de fechar?"),
                                        QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel,
                                        QMessageBox::Save
                                     );
    return result;
}

void IDE::setDocumentText(Documento *document, QFile *file)
{
    //Seta o documento sujo para não adicionar o * ... por que ao adicionar o texto lido do arquivo no PlainTextEdit
    //ele irá chamar textChanged mas nessa situação não queremos que adicione o * ...
    document->sujou();

    //Coloca o texto do arquivo no PlainTextEdit
    document->setTextoDocumento(file->readAll());

    //agora marca o texto como limpo...
    document->limpou();
}

QFile *IDE::abrirArquivoLeitura(QString &fileName)
{
    //Abrir o arquivo...
    QFile *file = new QFile(fileName);

    //Verificar se o arquivo está aberto...
    if (!file->open(QIODevice::ReadOnly | QIODevice::Text))
    {
        //Exibir mensagem de erro...
        QMessageBox msg;
        msg.setWindowTitle("Erro ao abrir o arquivo");
        msg.setText("Erro ao tentar abrir o arquivo ");
        msg.setInformativeText(file->errorString());
        msg.exec();

        //se deu erro deleta o arquivo
        delete file;

        //retorna NULL...
        return NULL;
    }

    //Senao retorna o arquivo...
    return file;
}

QFile *IDE::abrirArquivoGravacao(QString &fileName)
{
    //Abrir o arquivo...
    QFile *file = new QFile(fileName);

    //Verificar se o arquivo está aberto...
    //Verifica se é possivel gravar no arquivo...
    if (!file->open(QIODevice::WriteOnly | QIODevice::Text))
    {
        //Cria mensagem de erro...
        QMessageBox msgBox;
        msgBox.setWindowTitle("CafezinhoIDE");
        msgBox.setText("Erro ao tentar salvar o arquivo");
        msgBox.setInformativeText(file->errorString());
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setDefaultButton(QMessageBox::Ok);
        msgBox.exec();

        //se deu erro deleta o arquivo
        delete file;

        //retorna NULL...
        return NULL;
    }

    //Senao retorna o arquivo...
    return file;
}

void IDE::reabrirAba(QString &fileName)
{
    //Pega o documento e seta o focus
    Documento * doc = docMan.procurar(fileNameToFileId(fileName));

    //Seta a tab encontrada como atual...
    this->ui->tabWidgetArquivos->setCurrentWidget(doc->getWidget());

    //Seta o focus
    doc->setFocus();
}

void IDE::fecharFile(QFile *file)
{
    file->close();;
    delete file;
}

QString IDE::getRealFileName(QString &fileName)
{
    return fileName.section(QDir::separator(),-1);
}

void IDE::setAbaTitle(int index, QString title)
{
    this->ui->tabWidgetArquivos->setTabToolTip(index, title);
}

void IDE::setCurrentAba(QWidget *widget)
{
    this->ui->tabWidgetArquivos->setCurrentWidget(widget);
}

void IDE::setCurrentAba(int index)
{
    this->ui->tabWidgetArquivos->setCurrentIndex(index);
}

int IDE::getCurrentAba()
{
    return this->ui->tabWidgetArquivos->currentIndex();
}

void IDE::setTabToolTip(int index, QString &tip)
{
    this->ui->tabWidgetArquivos->setTabToolTip(index,tip);
}

void IDE::removeAba(int index, Documento *document)
{
    //remove o tab
    this->ui->tabWidgetArquivos->removeTab(index);

    //remove o tab da hash
    docMan.remover(index);

    //remove o arquivo da tabela de aberto: se não estava aberto não acontece nada.
    fileOpened.remove(document->getDocumentoId());

    //Deleta o container do documento...
    delete document;
}

bool IDE::writeDocument(Documento *document, QString &fileName)
{
    //Adiciona a terminação .cafe se o usuario não informar
    if(!fileName.contains(".cafe"))
    {
        fileName+=".cafe";
    }

    QFile * file = abrirArquivoGravacao(fileName);

    if(file!=NULL)
    {
        //Grava arquivo no disco...
        QTextStream out(file);
        out<<document->getTextoDocumento();
        fecharFile(file);
        return true;
    }

    return false;
}


bool IDE::readDocument(Documento *document, QString &fileName)
{
    //Abrir o arquivo...
    QFile* file = abrirArquivoLeitura(fileName);
    int index = 0;

    if(file!=NULL)
    {
        if(document->isVazio()&&(!document->isAberto()))
        {
            setDocumentText(document, file);
            index = getCurrentAba();
        }
        else
        {
            //Cria um conteiner para guardar informações sobre o documento aberto
            Documento* doc = criarAba(getRealFileName(fileName), &index);
            setDocumentText(doc, file);

        }

        configurarDocumento(document, fileName, index);
        fecharFile(file);

        return true;
    }

    return false;
}

void IDE::configurarDocumento(Documento *document, QString &fileName, int index)
{
    //Seta o titulo da aba
    setAbaTitle(index, getRealFileName(fileName));

    //Seta o nome do documento
    document->setNomeDocumento(fileName);

    //Seta o documento como aberto
    document->abriu();

    //seta o documento como cleaned
    document->limpou();

    //Seta o toolTip da aba
    setTabToolTip(index, fileName);

    //Ajusta a variavel lastPath para o ultimo arquivo aberto
    lastPath = fileName.remove(getRealFileName(fileName));

    //Inseri o arquivo na tabela de arquivos abertos
    fileOpened.insert(document->getDocumentoId());

    //seta focus no edit
    document->setFocus();
}

void IDE::actionAbrirClicked(bool checked)
{
    //Abrir a janela pedindo ao usuario que entre com o arquivo...
    QString fileName = showAbrirArquivo();

    if(fileName.isEmpty())
        return;

    //Verifica se o editor já está com aquele arquivo aberto e senão o tiver aberto, ele o abre.
    if(!fileOpened.contains(fileNameToFileId(fileName)))
    {
        //pega o index do tab atual
        int index = getCurrentAba();

        //Pega o edit da hashtable
        Documento* doc = docMan.procurar(index);

        //Ler documento...
        readDocument(doc,fileName);
    }
    else
    {
        reabrirAba(fileName);
    }
}

void IDE::actionNovoClicked(bool checked)
{
    Documento *doc = criarAba(tr("Novo Arquivo"));

    //inseri a tab na Hashtable...
    docMan.inserir(doc);

    //Seta o foco no edit...
    doc->setFocus();
}

void IDE::actionFecharClicked(bool checked)
{
    //pega o index do tab atual
    int index = getCurrentAba();

    //Pega o edit da hashtable
    Documento* doc = docMan.procurar(index);

    //Verifica se existe mais de uma aba...
    if(arquivos.size()>1)
    {
        if(doc->isSujo())
        {
            //Perqunta se pode fechar assim mesmo
            switch(showSalvarAlteracao())
            {
                case QMessageBox::Save:
                {
                    QString fileName;
                    if(doc->isAberto())
                        fileName = doc->getCaminhoCompleto();
                    else
                        fileName = showSalvarArquivo(doc->getCaminhoCompleto());

                    //Se estiver vazia não fecha a aba...
                    if(fileName.isEmpty())
                        return;

                    if(!writeDocument(doc, fileName))
                    {
                        //se der erro (nesse ponto a mensagem de erro já ocorreu) eu apenas fecho... que o usuario
                        //vai tentar novamente ...
                        return;
                    }
                }
                break;
                case QMessageBox::Cancel:
                {
                    return;
                }
                break;
            }
        }

        removeAba(index, doc);
    }

    //se existir apenas essa aba não a fecha e tbm não aparece janela de salva (apenas não fecha)...
}

void IDE::actionSairClicked(bool checked)
{
    int index = 0;

    for(QList<Documento*>::iterator it = docMan.begin(); it!= docMan.end(); it++, index++)
    {
        Documento *doc = (*it);

        if(doc->isSujo())
        {

            //Seta a tab index como a atual...
            setCurrentAba(index);

            //Seta o foco no edit...
            doc->setFocus();

            switch(showSalvarAlteracao())
            {
                case QMessageBox::Cancel:
                {
                    return;
                }
                break;
                case QMessageBox::Save:
                {
                    QString fileName;
                    if(doc->isAberto())
                        fileName = doc->getCaminhoCompleto();
                    else
                        fileName = showSalvarArquivo(doc->getCaminhoCompleto());

                    //Se estiver vazia não fecha a aba...
                    if(fileName.isEmpty())
                        return;

                    if(!writeDocument(doc, fileName))
                    {
                        //se der erro (nesse ponto a mensagem de erro já ocorreu) eu apenas fecho... que o usuario
                        //vai tentar novamente ...
                        return;
                    }

                }
                break;
            }

        }
        removeAba(index, doc);
    }

    qApp->exit(0);
}

void IDE::actionSalvarClicked(bool checked)
{
    //pega o index do tab atual
    int index = this->ui->tabWidgetArquivos->currentIndex();

    //Pega o edit da hashtable
    Documento* doc = docMan.procurar(index);

    QString fileName;

    bool salvar_como = false;

    if(doc->isAberto())
    {
        fileName = doc->getCaminhoCompleto();
        salvar_como = true;
    }
    else
        fileName = showSalvarArquivo(doc->getCaminhoCompleto());

    //Se estiver vazia não salva nada...
    if(fileName.isEmpty())
        return;

    salvarDocumento(doc, fileName, index, salvar_como);
}

void IDE::actionSalvarComoClicked(bool checked)
{
    //pega o index do tab atual
    int index = this->ui->tabWidgetArquivos->currentIndex();

    //Pega o edit da hashtable
    Documento* doc = docMan.procurar(index);

    //A onde salvar
    QString fileName = showSalvarArquivo();

    //Se estiver vazia não salva nada...
    if(fileName.isEmpty())
        return;

    salvarDocumento(doc, fileName, index, true);

}

void IDE::salvarDocumento(Documento *document, QString &fileName, int index, bool salvar_como)
{

    if(!writeDocument(document,fileName))
        return;

    if(salvar_como)
    {
        //remove o antigo file...
        fileOpened.remove(document->getDocumentoId());
    }

    configurarDocumento(document, fileName, index);
}

void IDE::plainTextEditTextChanged()
{

    //pega o index do tab atual
    int index = this->ui->tabWidgetArquivos->currentIndex();

    //Pega o edit da hashtable
    Documento* doc = docMan.procurar(index);

    if(!doc->isSujo())
    {

        //poem o texto no lugar
        QString text = this->ui->tabWidgetArquivos->tabText(index);
        text+="*";
        this->ui->tabWidgetArquivos->setTabText(index, text);
        doc->sujou();
    }
}

void IDE::actionNumero_da_linhaToggled(bool checked)
{
    CodeEditor::setLineNumber(checked);

    //pega o index do tab atual
    int index = this->ui->tabWidgetArquivos->currentIndex();

    //Pega o edit da hashtable
    Documento* doc = docMan.procurar(index);

    //Repintar o edit
    doc->repaintEdit();
}

void IDE::breakpoint(int line, bool checked)
{
    qDebug()<<line<<", "<<checked;
}
