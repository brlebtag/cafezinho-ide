#include "ide.h"
#include "ui_ide.h"

const void* IDE::null = 0;

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
    Document* doc = new Document(this->ui->tabWidgetArquivos->currentWidget(), edit);

    //inseri a tab na Hashtable
    docMan.insert(document);

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

Document *IDE::criarAba(QString title)
{
    //Criar a aba..
    QWidget* tab = new QWidget(this->ui->tabWidgetArquivos);

    //Inseri a aba no tabWidget o titulo é apenas a ultima parte do caminho full do arquivo (só o nome do arquivo)
    int index = this->ui->tabWidgetArquivos->addTab(tab, title);

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
    Document* doc = new Document(tab, edit);

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

void IDE::setDocumentText(Document *document, QFile *file)
{
    //Seta o documento sujo para não adicionar o * ... por que ao adicionar o texto lido do arquivo no PlainTextEdit
    //ele irá chamar textChanged mas nessa situação não queremos que adicione o * ...
    document->gotDirty();

    //Coloca o texto do arquivo no PlainTextEdit
    document->setText(file->readAll());

    //agora marca o texto como limpo...
    document->gotCleaned();
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
        return (QFile*)IDE::null;
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
        return (QFile*)IDE::null;
    }

    //Senao retorna o arquivo...
    return file;
}

void IDE::reabrirAba(QString &fileName)
{
    //Pega o documento e seta o focus
    Document * doc = docMan.search(fileNameToFileId(fileName));

    //Seta a tab encontrada como atual...
    this->ui->tabWidgetArquivos->setCurrentIndex(doc->getWidget());

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

void IDE::removeAba(int index, Document *document)
{
    //remove o tab
    this->ui->tabWidgetArquivos->removeTab(index);

    //remove o tab da hash
    docMan.remove(index);

    //remove o arquivo da tabela de aberto: se não estava aberto não acontece nada.
    fileOpened.remove(document->getFileId());

    //Deleta o container do documento...
    delete document;
}

bool IDE::writeDocument(Document *document, QString &fileName)
{
    //Adiciona a terminação .cafe se o usuario não informar
    if(!fileName.contains(".cafe"))
    {
        fileName+=".cafe";
    }

    QFile * file = abrirArquivoGravacao(fileName);

    if(file!=IDE::null)
    {
        //Grava arquivo no disco...
        QTextStream out(file);
        out<<document->getText();
        fecharFile(file);
        return true;
    }

    return false;
}

void IDE::readDocument(Document *document, int index, QString &fileName, QFile *file)
{
    //Seta o conteudo do arquivo...
    setDocumentText(document, file);

    //Seta o titulo da aba
    setAbaTitle(index, getRealFileName(fileName));

    //Seta o nome do documento
    document->setFileName(fileName);

    //Seta o documento como aberto
    document->gotOpened();

    //Seta o toolTip da aba
    setTabToolTip(index, fileName);

    //Ajusta a variavel lastPath para o ultimo arquivo aberto
    lastPath = fileName.remove(getRealFileName(fileName));

    //Inseri o arquivo na tabela de arquivos abertos
    fileOpened.insert(document->getFileId());

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
        Document* doc = docMan.search(index);

        //Abrir o arquivo...
        QFile* file = abrirArquivoLeitura(fileName);

        if(file!=IDE::null)
        {
            if(doc->isEmpty())
            {
                readDocument(doc, index, fileName, file);
            }
            else
            {
                //Cria um conteiner para guardar informações sobre o documento aberto
                Document* doc = criarAba(getRealFileName(fileName));
                readDocument(doc, index, fileName, file);
            }
            fecharFile(file);
        }
    }
    else
    {
        reabrirAba(fileName);
    }
}

void IDE::actionNovoClicked(bool checked)
{
    Document *doc = criarAba(tr("Novo Arquivo"));

    //inseri a tab na Hashtable...
    docMan.insert(doc);

    //Seta o foco no edit...
    doc->setFocus();
}

void IDE::actionFecharClicked(bool checked)
{
    //pega o index do tab atual
    int index = getCurrentAba();

    //Pega o edit da hashtable
    Document* doc = docMan.search(index);

    //Verifica se existe mais de uma aba...
    if(arquivos.size()>1)
    {
        if(doc->isDirty())
        {
            //Perqunta se pode fechar assim mesmo
            switch(showSalvarAlteracao())
            {
                case QMessageBox::Save:
                {
                    QString fileName;
                    if(doc->isOpened())
                        fileName = doc->getPath();
                    else
                        fileName = showSalvarArquivo(doc->getPath());

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

    for(QList<Document*>::iterator it = docMan.begin(); it!= docMan.end(); it++, index++)
    {
        Document *doc = (*it);

        if(doc->isDirty())
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
                    if(doc->isOpened())
                        fileName = doc->getPath();
                    else
                        fileName = showSalvarArquivo(doc->getPath());

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
    Document* doc = docMan.search(index);

    QString fileName;

    bool salvar_como = false;

    if(doc->isOpened())
    {
        fileName = doc->getPath();
        salvar_como = true;
    }
    else
        fileName = showSalvarArquivo(doc->getPath());

    //Se estiver vazia não salva nada...
    if(fileName.isEmpty())
        return;


    QFile* file = abrirArquivoGravacao(fileName);

    if(file!=IDE::null)
    {

        if(!writeDocument(doc,fileName))
            return;

        //Se foi salvar como então o arquivo possivelmente mudou de local e agora estamos trabalhando naquele local...
        if(salvar_como)
        {
            //remove o antigo file...
            fileOpened.remove(doc->getFileId());

            doc->setFileName(fileName);

            //Reinsere o novo...
            fileOpened.insert(doc->getFileId());

        }

        //seta o tooltip
        setTabToolTip(index, fileName);

        //seta o titulo da aba
        setAbaTitle(index, getRealFileName(fileName));

        //fecha o arquivo
        fecharFile(file);

        //Marca o documento como limpo
        doc->gotCleaned();
    }
}

void IDE::actionSalvarComoClicked(bool checked)
{
    //pega o index do tab atual
    int index = this->ui->tabWidgetArquivos->currentIndex();

    //Pega o edit da hashtable
    Document* doc = docMan.search(index);

    //A onde salvar
    QString fileName = showSalvarArquivo();

    //Se estiver vazia não salva nada...
    if(fileName.isEmpty())
        return;

    //Adiciona a terminação .cafe se o usuario não informar
    if(!fileName.contains(".cafe"))
    {
        fileName+=".cafe";
    }

    //apenas salva o arquivo
    QFile *file = abrirArquivoGravacao(fileName);

    if(file!=IDE::null)
    {

        if(!writeDocument(doc,fileName))
            return;

        //remove o antigo file...
        fileOpened.remove(doc->getFileId());

        //reinsere o nome...
        doc->setFileName(fileName);

        //Reinsere o novo...
        fileOpened.insert(doc->getFileId());

        //seta o tooltip
        setTabToolTip(index, fileName);

        //seta o titulo da aba
        setAbaTitle(index, getRealFileName(fileName));

        //fecha o arquivo
        fecharFile(file);
    }

}

void IDE::plainTextEditTextChanged()
{

    //pega o index do tab atual
    int index = this->ui->tabWidgetArquivos->currentIndex();

    //Pega o edit da hashtable
    Document* doc = docMan.search(index);

    if(!doc->isDirty())
    {

        //poem o texto no lugar
        QString text = this->ui->tabWidgetArquivos->tabText(index);
        text+="*";
        this->ui->tabWidgetArquivos->setTabText(index, text);
        doc->gotDirty();
    }
}

void IDE::actionNumero_da_linhaToggled(bool checked)
{
    CodeEditor::setLineNumber(checked);

    //pega o index do tab atual
    int index = this->ui->tabWidgetArquivos->currentIndex();

    //Pega o edit da hashtable
    Document* doc = docMan.search(index);

    //Repintar o edit
    doc->repaintEdit();
}

void IDE::breakpoint(int line, bool checked)
{
    qDebug()<<line<<", "<<checked;
}
