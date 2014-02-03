#include "ide.h"
#include "ui_ide.h"


IDE::IDE(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::IDE)
{
    ui->setupUi(this);

    connect(this->ui->actionAbrir,SIGNAL(triggered()),this,SLOT(acaoAbrir()));
    connect(this->ui->actionNovo,SIGNAL(triggered(bool)),this,SLOT(acaoNovo(bool)));
    connect(this->ui->actionFechar,SIGNAL(triggered(bool)),this,SLOT(acaoFechar(bool)));
    connect(this->ui->actionSair,SIGNAL(triggered(bool)),this,SLOT(acaoSair(bool)));
    connect(this->ui->actionSalvar,SIGNAL(triggered(bool)),this,SLOT(acaoSalvar(bool)));
    connect(this->ui->actionSalvar_Como,SIGNAL(triggered(bool)),this,SLOT(acaoSalvarComo(bool)));
    connect(this->ui->actionNumero_da_Linha,SIGNAL(toggled(bool)),this,SLOT(acaoHabilitarNumeroLinha(bool)));

    //Index da aba atual...
    int index = this->ui->tabWidgetArquivos->currentIndex();

    //Cria um QPlainTextEdit e inseri na tab
    EditorCodigo *edit = new EditorCodigo(this->ui->tabWidgetArquivos->currentWidget());

    //adiciona o connect para salvar as mudanças no texto...
    connect(edit,SIGNAL(textChanged()),this,SLOT(alterarEditorCodigo()));

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
    ultimoCaminho = QDir::currentPath();

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
    EditorCodigo *edit = new EditorCodigo(tab);

    //adiciona o connect para salvar as mudanças no texto...
    connect(edit,SIGNAL(textChanged()),this,SLOT(alterarEditorCodigo()));

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

QString IDE::nomeDocParaDocId(QString &fileName)
{
    return QCryptographicHash::hash(fileName.toUtf8(),QCryptographicHash::Md5).toHex();
}

QString IDE::mostrarAbrirArquivo()
{
    //Abrir a janela pedindo ao usuario que entre com o arquivo... e retorna a string
    mostrarAbrirArquivo(ultimoCaminho);
}

QString IDE::mostrarAbrirArquivo(QString &path)
{
    //Abrir a janela pedindo ao usuario que entre com o arquivo... e retorna a string
    return QFileDialog::getOpenFileName(this, tr("Abrir Arquivo"), path, tr("Files (*.cafe)"));
}

QString IDE::mostrarSalvarArquivo()
{
    return mostrarSalvarArquivo(ultimoCaminho);
}

QString IDE::mostrarSalvarArquivo(QString path)
{
    return QFileDialog::getSaveFileName(this, tr("Salvar Arquivo"),path, tr("Arquivo Cafezinho(*.cafe)"), new QString(tr("Arquivo Cafezinho (*.cafe)")));
}

int IDE::mostrarSalvarAlteracao()
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

void IDE::setTextoDocumento(Documento *document, QFile *file)
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
    Documento * doc = docMan.procurar(nomeDocParaDocId(fileName));

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

QString IDE::getNomeDocumento(QString &fileName)
{
    return fileName.section(QDir::separator(),-1);
}

void IDE::setTituloAba(int index, QString title)
{
    this->ui->tabWidgetArquivos->setTabToolTip(index, title);
}

void IDE::setAbaAtual(QWidget *widget)
{
    this->ui->tabWidgetArquivos->setCurrentWidget(widget);
}

void IDE::setAbaAtual(int index)
{
    this->ui->tabWidgetArquivos->setCurrentIndex(index);
}

int IDE::getAbaAtual()
{
    return this->ui->tabWidgetArquivos->currentIndex();
}

void IDE::setDicaAba(int index, QString &tip)
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
    docAbertos.remove(document->getDocumentoId());

    //Deleta o container do documento...
    delete document;
}

bool IDE::gravarDocumento(Documento *document, QString &fileName)
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


bool IDE::lerDocument(Documento *document, QString &fileName)
{
    //Abrir o arquivo...
    QFile* file = abrirArquivoLeitura(fileName);
    int index = 0;

    if(file!=NULL)
    {
        if(document->isVazio()&&(!document->isAberto()))
        {
            setTextoDocumento(document, file);
            index = getAbaAtual();
        }
        else
        {
            //Cria um conteiner para guardar informações sobre o documento aberto
            Documento* doc = criarAba(getNomeDocumento(fileName), &index);
            setTextoDocumento(doc, file);

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
    setTituloAba(index, getNomeDocumento(fileName));

    //Seta o nome do documento
    document->setNomeDocumento(fileName);

    //Seta o documento como aberto
    document->abriu();

    //seta o documento como cleaned
    document->limpou();

    //Seta o toolTip da aba
    setDicaAba(index, fileName);

    //Ajusta a variavel lastPath para o ultimo arquivo aberto
    ultimoCaminho = fileName.remove(getNomeDocumento(fileName));

    //Inseri o arquivo na tabela de arquivos abertos
    docAbertos.insert(document->getDocumentoId());

    //seta focus no edit
    document->setFocus();
}

void IDE::acaoAbrir(bool checked)
{
    //Abrir a janela pedindo ao usuario que entre com o arquivo...
    QString fileName = mostrarAbrirArquivo();

    if(fileName.isEmpty())
        return;

    //Verifica se o editor já está com aquele arquivo aberto e senão o tiver aberto, ele o abre.
    if(!docAbertos.contains(nomeDocParaDocId(fileName)))
    {
        //pega o index do tab atual
        int index = getAbaAtual();

        //Pega o edit da hashtable
        Documento* doc = docMan.procurar(index);

        //Ler documento...
        lerDocument(doc,fileName);
    }
    else
    {
        reabrirAba(fileName);
    }
}

void IDE::acaoNovo(bool checked)
{
    Documento *doc = criarAba(tr("Novo Arquivo"));

    //inseri a tab na Hashtable...
    docMan.inserir(doc);

    //Seta o foco no edit...
    doc->setFocus();
}

void IDE::acaoFechar(bool checked)
{
    //pega o index do tab atual
    int index = getAbaAtual();

    //Pega o edit da hashtable
    Documento* doc = docMan.procurar(index);

    //Verifica se existe mais de uma aba...
    if(arquivos.size()>1)
    {
        if(doc->isSujo())
        {
            //Perqunta se pode fechar assim mesmo
            switch(mostrarSalvarAlteracao())
            {
                case QMessageBox::Save:
                {
                    QString fileName;
                    if(doc->isAberto())
                        fileName = doc->getCaminhoCompleto();
                    else
                        fileName = mostrarSalvarArquivo(doc->getCaminhoCompleto());

                    //Se estiver vazia não fecha a aba...
                    if(fileName.isEmpty())
                        return;

                    if(!gravarDocumento(doc, fileName))
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

void IDE::acaoSair(bool checked)
{
    int index = 0;

    for(QList<Documento*>::iterator it = docMan.begin(); it!= docMan.end(); it++, index++)
    {
        Documento *doc = (*it);

        if(doc->isSujo())
        {

            //Seta a tab index como a atual...
            setAbaAtual(index);

            //Seta o foco no edit...
            doc->setFocus();

            switch(mostrarSalvarAlteracao())
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
                        fileName = mostrarSalvarArquivo(doc->getCaminhoCompleto());

                    //Se estiver vazia não fecha a aba...
                    if(fileName.isEmpty())
                        return;

                    if(!gravarDocumento(doc, fileName))
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

void IDE::acaoSalvar(bool checked)
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
        fileName = mostrarSalvarArquivo(doc->getCaminhoCompleto());

    //Se estiver vazia não salva nada...
    if(fileName.isEmpty())
        return;

    salvarDocumento(doc, fileName, index, salvar_como);
}

void IDE::acaoSalvarComo(bool checked)
{
    //pega o index do tab atual
    int index = this->ui->tabWidgetArquivos->currentIndex();

    //Pega o edit da hashtable
    Documento* doc = docMan.procurar(index);

    //A onde salvar
    QString fileName = mostrarSalvarArquivo();

    //Se estiver vazia não salva nada...
    if(fileName.isEmpty())
        return;

    salvarDocumento(doc, fileName, index, true);

}

void IDE::salvarDocumento(Documento *document, QString &fileName, int index, bool salvar_como)
{

    if(!gravarDocumento(document,fileName))
        return;

    if(salvar_como)
    {
        //remove o antigo file...
        docAbertos.remove(document->getDocumentoId());
    }

    configurarDocumento(document, fileName, index);
}

void IDE::alterarEditorCodigo()
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

void IDE::acaoHabilitarNumeroLinha(bool checked)
{
    EditorCodigo::setLineNumber(checked);

    //pega o index do tab atual
    int index = this->ui->tabWidgetArquivos->currentIndex();

    //Pega o edit da hashtable
    Documento* doc = docMan.procurar(index);

    //Repintar o edit
    doc->repintarEditor();
}

void IDE::breakpoint(int line, bool checked)
{
    qDebug()<<line<<", "<<checked;
}
