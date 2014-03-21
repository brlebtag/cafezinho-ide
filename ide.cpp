#include "ide.h"
#include "ui_ide.h"


IDE::IDE(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::IDE),
    genReabrir(this),
    genProc(this),
    configuracoes(QSettings::IniFormat, QSettings::UserScope, "UFG", "CafezinhoIDE")
{
    ui->setupUi(this);

    //Configurando os sinais...

    //Menu Arquivo
    connect(this->ui->actionAbrir,SIGNAL(triggered()),this,SLOT(acaoAbrir()));
    connect(this->ui->actionNovo,SIGNAL(triggered()),this,SLOT(acaoNovo()));
    connect(this->ui->actionFechar,SIGNAL(triggered()),this,SLOT(acaoFechar()));
    connect(this->ui->actionSair,SIGNAL(triggered()),this,SLOT(acaoSair()));
    connect(this->ui->actionSalvar,SIGNAL(triggered()),this,SLOT(acaoSalvar()));
    connect(this->ui->actionSalvar_Como,SIGNAL(triggered()),this,SLOT(acaoSalvarComo()));
    connect(this->ui->menuArquivo,SIGNAL(aboutToShow()),this,SLOT(menuArquivoClicado()));

    //Menu Ver
    connect(this->ui->actionNumero_da_Linha,SIGNAL(toggled(bool)),this,SLOT(acaoHabilitarNumeroLinha(bool)));
    connect(this->ui->actionFuncoes,SIGNAL(toggled(bool)),this,SLOT(acaoHabilitarFuncoes(bool)));
    connect(this->ui->actionDebugger,SIGNAL(toggled(bool)),this,SLOT(acaoHabilitarDebug(bool)));
    connect(this->ui->actionExecProg,SIGNAL(toggled(bool)),this,SLOT(acaoHabilitarExecProg(bool)));
    connect(this->ui->actionBarraFerramentas,SIGNAL(toggled(bool)),this,SLOT(acaoHabilitarBarraFerramentas(bool)));
    connect(this->ui->actionBarraStatus,SIGNAL(toggled(bool)),this,SLOT(acaoHabilitarBarraStatus(bool)));
    connect(this->ui->actionReiniciar,SIGNAL(triggered()), this,SLOT(reiniciarInterfaceClicado()));

    //Menu Documento
    connect(this->ui->actionProximoDocumento,SIGNAL(triggered()),this,SLOT(proximoDocumento()));
    connect(this->ui->actionAnteriorDocumento,SIGNAL(triggered()),this,SLOT(anteriroDocumento()));
    connect(this->ui->actionSalvarTodos,SIGNAL(triggered()),this,SLOT(salvarTodosDocumentos()));
    connect(this->ui->actionFecharTodos,SIGNAL(triggered()),this,SLOT(fecharTodosDocumentos()));

    //Menu Editar
    connect(this->ui->menuEditar,SIGNAL(aboutToShow()),this,SLOT(menuEditarClicado()));
    connect(this->ui->actionCopiar,SIGNAL(triggered()),this,SLOT(copiarDocumento()));
    connect(this->ui->actionColar,SIGNAL(triggered()),this,SLOT(colarDocumento()));
    connect(this->ui->actionRecortar,SIGNAL(triggered()),this,SLOT(recortarDocumento()));
    connect(this->ui->actionDesfazer,SIGNAL(triggered()),this,SLOT(desfazerDocumento()));
    connect(this->ui->actionRefazer,SIGNAL(triggered()),this,SLOT(refazerDocumento()));
    connect(this->ui->actionDuplica,SIGNAL(triggered()),this,SLOT(duplicarLinhar()));

    //Menu Editor
    connect(this->ui->actionMaior,SIGNAL(triggered()),this,SLOT(aumentarFonte()));
    connect(this->ui->actionMenor,SIGNAL(triggered()),this,SLOT(diminuirFonte()));
    connect(this->ui->actionResetar,SIGNAL(triggered()),this,SLOT(reiniciarFonte()));
    connect(this->ui->actionFonte,SIGNAL(triggered()),this,SLOT(fonteClicado()));

    //Menu Pesquisar
    connect(this->ui->actionIr_para_Linha,SIGNAL(triggered()),this,SLOT(irParaClicado()));
    connect(this->ui->actionLocalizar,SIGNAL(triggered()),this,SLOT(localizarClicado()));
    connect(this->ui->actionSubstituir,SIGNAL(triggered()),this,SLOT(substituirClicado()));
    connect(this->ui->actionLocalizar_Anterior,SIGNAL(triggered()),this,SLOT(localizarAnteriroClicado()));
    connect(this->ui->actionLocalizar_Proximo,SIGNAL(triggered()),this,SLOT(localizarProximoClicado()));

    //Tab Widget Arquivos
    connect(this->ui->tabWidgetArquivos,SIGNAL(currentChanged(int)),this, SLOT(mudouAbaAtual(int)));

    //Conecto o menu reabrir para receber quando um item do menu for clicado para reabrir ele...
    connect(&genReabrir,SIGNAL(menuReabrirClicou(QString)),this,SLOT(menuReabrirClicou(QString)));

    Documento* doc = criarDocumento("Novo Arquivo");

    //Inserir Botao nova Aba no canto direto da  TabWidget...
    this->ui->tabWidgetArquivos->setCornerWidget(criarBotaoMaisAba(this->ui->tabWidgetArquivos),Qt::TopRightCorner);

    //Seta o foco no edit...
    doc->setFocus();

    //inseri a tab na gerenciador de documentos
    genDoc.inserir(doc);

    //remove a primeira Aba para controlar melhor o gerenciamento de aba...
    this->ui->tabWidgetArquivos->removeTab(0);

    //Inseri o menu no Reabrir...
    this->ui->actionReabrir->setMenu(this->genReabrir.getMenu());

    //Seta status Bar como pronto
    this->ui->statusBar->showMessage("Pronto", 0);
    this->ui->statusBar->setStatusTip("Pronto");

    //Restaurar Todas as configurações
    restaurarConfiguracoes();

    //Adicionar o tabEdit no genProc
    genProc.setTabWidget(this->ui->tabgadget);

    //Adicionar o edit
    genProc.setEditorProcurar(doc->getEditor());

    //Ajusta o ultimo caminho
    ultimoCaminho = genReabrir.getUltimoCaminho();
}

void IDE::restaurarConfiguracoesFonte()
{
    //Funções...
    tamanho_fonte = configuracoes.value("tamanho_fonte", 9).toInt();
    familia_fonte = configuracoes.value("familia_fonte","sans-serif").toString();

    configurarFonteEditor();
}

void IDE::restaurarConfiguracoesMenuVer()
{
    //Funções...
    ver_funcoes = configuracoes.value("ver_funcoes", true).toBool();
    this->ui->actionFuncoes->setChecked(ver_funcoes);

    //Debug
    ver_debugger = configuracoes.value("ver_debugger", true).toBool();
    this->ui->actionDebugger->setChecked(ver_debugger);

    //Debug
    ver_exec_prog = configuracoes.value("ver_exec_prog", true).toBool();
    this->ui->actionExecProg->setChecked(ver_exec_prog);

    //Barra de Ferrramentas
    ver_barra_ferramentas = configuracoes.value("ver_barra_ferramentas", true).toBool();
    this->ui->actionBarraFerramentas->setChecked(ver_barra_ferramentas);

    //Barra de Status
    ver_barra_status = configuracoes.value("ver_barra_status", true).toBool();
    this->ui->actionBarraStatus->setChecked(ver_barra_status);
}

void IDE::closeEvent(QCloseEvent *event)
{

    if(!salvarEFecharAbas())
    {
        //Teve algum problema em fechar as abas então ignora
        event->ignore();

        //retorna sem fechar
        return;
    }

    //Grava todas as configurações
    gravarConfiguracoes();

    //Aceita o evento...
    event->accept();
}

void IDE::gravarConfiguracoesMenuVer()
{
    //Grava as informacoes da Configuracao

    configuracoes.setValue("ver_funcoes", ver_funcoes);

    configuracoes.setValue("ver_debugger", ver_debugger);

    configuracoes.setValue("ver_exec_prog", ver_exec_prog);

    configuracoes.setValue("ver_barra_ferramentas", ver_barra_ferramentas);

    configuracoes.setValue("ver_barra_status", ver_barra_status);
}

void IDE::gravarConfiguracoesFonte()
{
    configuracoes.setValue("tamanho_fonte", tamanho_fonte);

    configuracoes.setValue("familia_fonte", familia_fonte);
}

void IDE::restaurarConfiguracoes()
{
    //Carregando Configurações sobre o menu Ver...
    restaurarConfiguracoesMenuVer();

    //Carregand Configurações sobre a fonte do edito
    restaurarConfiguracoesFonte();
}

IDE::~IDE()
{
    //deleta o HashTable
    delete ui;
}

QWidget* IDE::criarAba(QString title, int *index, QWidget*tab, QWidget* botao)
{

    //Inseri a aba no tabWidget o titulo é apenas a ultima parte do caminho full do arquivo (só o nome do arquivo)
    int id = this->ui->tabWidgetArquivos->addTab(tab, title);

    //se recebeu index como parametro...
    if(index != 0)
        (*index) = id;

    //seta a nova aba como atual
    this->ui->tabWidgetArquivos->setCurrentWidget(tab);

    //Inseri o botao
    this->ui->tabWidgetArquivos->tabBar()->setTabButton(id, QTabBar::RightSide, botao);

    return tab;
}

QPushButton *IDE::criarBotaoFecharAba(QWidget *pai)
{
    //Cria um botao
    QPushButton *button = new QPushButton(pai);

    //Seta o Icon do botão
    button->setIcon(*(new QIcon(":/fechar.png")));

    //Seta o tamanho maximo
    button->setFixedWidth(20);
    button->setFixedHeight(20);

    //Conecta o sinal para receber quando este for clicado
    connect(button,SIGNAL(clicked()),this,SLOT(botaoFecharTabClicado()));

    return button;
}

QPushButton *IDE::criarBotaoMaisAba(QWidget *pai)
{
    //Cria um botao
    QPushButton *button = new QPushButton(pai);

    //Seta o Icon do botão
    button->setIcon(*(new QIcon(":/mais.png")));

    //Conecta o sinal para receber quando este for clicado
    connect(button,SIGNAL(clicked()),this,SLOT(botaoMaisTabClicado()));

    return button;
}

EditorCodigo* IDE::criarEditor(QWidget* aba)
{
    //Cria um QPlainTextEdit e inseri na nova tab
    EditorCodigo *edit = new EditorCodigo(aba);

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
    aba->setLayout(layout);

    return edit;
}

Documento* IDE::criarDocumento(QString title, int *index)
{
    //Criar a aba..
    QWidget* tab = new QWidget();

    //Cria botão
    QWidget *botao = (QWidget*) (criarBotaoFecharAba(tab));

    //Criar a aba
    QWidget* aba = criarAba(title, index, tab, botao);

    //Criar o EditorCodigo
    EditorCodigo* edit = criarEditor(aba);

    //Retorna um documento...
    return new Documento(aba, edit, botao);
}

QString IDE::nomeDocParaDocId(QString &fileName)
{
    return QCryptographicHash::hash(fileName.toUtf8(),QCryptographicHash::Md5).toHex();
}

QString IDE::mostrarAbrirArquivo()
{
    //Abrir a janela pedindo ao usuario que entre com o arquivo... e retorna a string
    return mostrarAbrirArquivo(ultimoCaminho);
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

void IDE::msgErroSalvar(QFile *file)
{
    QMessageBox msgBox;
    msgBox.setWindowTitle("CafezinhoIDE");
    msgBox.setText("Erro ao tentar salvar o arquivo: "+file->fileName());
    if(file!=0)
        msgBox.setInformativeText(file->errorString());
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.setDefaultButton(QMessageBox::Ok);
    msgBox.exec();
}

void IDE::msgErroAbrir(QFile *file)
{
    //Exibir mensagem de erro...
    QMessageBox msgBox;
    msgBox.setWindowTitle("CafezinhoIDE");
    msgBox.setText("Erro ao tentar abrir o arquivo"+file->fileName());
    if(file!=0)
        msgBox.setInformativeText(file->errorString());
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.setDefaultButton(QMessageBox::Ok);
    msgBox.exec();
}

int IDE::mostrarSalvarAlteracao()
{
    //Perqunta se pode fechar assim mesmo
    int result = QMessageBox::warning(
                                        this,tr("CafezinhoIDE"),
                                        tr("Deseja salvar as alterações?"),
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
        //Cria mensagem de erro...
        msgErroAbrir(file);

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
        msgErroSalvar(file);

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
    Documento * doc = genDoc.procurar(nomeDocParaDocId(fileName));

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
    return fileName.section("/",-1);
}

QString IDE::getCaminhoDocumento(QString &fileName)
{
    return fileName.remove(getNomeDocumento(fileName));
}

void IDE::setTituloAba(int index, QString title)
{
    this->ui->tabWidgetArquivos->setTabText(index, title);
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

QWidget *IDE::getAbaAtualWidget()
{
    return this->ui->tabWidgetArquivos->currentWidget();
}

Documento *IDE::getDocumentoAtual()
{
    return genDoc.procurar(getAbaAtual());
}

void IDE::setDicaAba(int index, QString &tip)
{
    this->ui->tabWidgetArquivos->setTabToolTip(index, tip);
}

void IDE::removeAba(int index, Documento *document)
{
    //remove o tab
    this->ui->tabWidgetArquivos->removeTab(index);

    //remove o tab da hash
    genDoc.remover(index);

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

    Documento *d;

    if(file!=NULL)
    {
        if(document->isVazio()&&(!document->isAberto()))
        {
            //Inseri o texto do arquivo no documento
            setTextoDocumento(document, file);

            //Pega o index da aba atual
            index = getAbaAtual();

            // O documento que será configurado é o document...
            d = document;

        }
        else
        {
            //Cria um conteiner para guardar informações sobre o documento aberto
            Documento* doc = criarDocumento(getNomeDocumento(fileName), &index);

            //Inserir documento no gerenciador de documento...
            genDoc.inserir(doc);

            //Inseri o texto do arquivo no documento
            setTextoDocumento(doc, file);

            //O documento que será configurado é doc e não document...
            d = doc;
        }

        //inicializa as configurações necessarias do documento
        configurarDocumento(d, fileName, index);

        //Fecha o arquivo...
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

    //seta o documento como limpo
    document->limpou();

    //Seta o toolTip da aba
    setDicaAba(index, fileName);

    //Ajusta a variavel lastPath para o ultimo arquivo aberto
    ultimoCaminho = getCaminhoDocumento(fileName);

    //Inseri o arquivo na tabela de arquivos abertos
    docAbertos.insert(document->getDocumentoId());

    //seta focus no edit
    document->setFocus();
}

void IDE::abrirDocumento(QString &fileName)
{
    bool result = false;
    QString caminho = fileName;

    //Verifica se o editor já está com aquele arquivo aberto e senão o tiver aberto, ele o abre.
    if(!docAbertos.contains(nomeDocParaDocId(fileName)))
    {
        //pega o index do tab atual
        int index = getAbaAtual();

        //Pega o edit no gerenciador de Documentos
        Documento* doc = genDoc.procurar(index);

        //Ler documento...
        result = lerDocument(doc,fileName);
    }
    else
    {
        reabrirAba(fileName);
        result= true;
    }
    if(result)
        genReabrir.atualizar(caminho);
}

void IDE::acaoAbrir()
{
    //Abrir a janela pedindo ao usuario que entre com o arquivo...
    QString fileName = mostrarAbrirArquivo();

    if(fileName.isEmpty())
        return;

    abrirDocumento(fileName);
}

void IDE::acaoNovo()
{
    //Cria uma nova aba...
    Documento *doc = criarDocumento(tr("Novo Arquivo"));

    //inseri a aba no gerenciador de documentos...
    genDoc.inserir(doc);

    //Seta o foco no edit...
    doc->setFocus();

    //Seta as configuraçẽos da fonte
    doc->setFonte(familia_fonte, tamanho_fonte);

    //forçar a seta a nova aba no genProc
    genProc.setEditorProcurar(doc->getEditor());
}

void IDE::acaoFechar(int indice)
{
    //pega o index do tab atual
    int index;

    if(indice == -1)
        index = getAbaAtual();
    else
        index = indice;

    //Pega o edit da hashtable
    Documento* doc = genDoc.procurar(index);
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
                    fileName = mostrarSalvarArquivo();

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

    if(genDoc.tamanho()==1)
        qApp->exit(0);

    removeAba(index, doc);
}

bool IDE::salvarAba(Documento* doc)
{
    QString fileName;
    if(doc->isAberto())
        fileName = doc->getCaminhoCompleto();
    else
        fileName = mostrarSalvarArquivo();

    //Se estiver vazia não fecha a aba...
    if(fileName.isEmpty())
        return false;

    if(!gravarDocumento(doc, fileName))
    {
        //se der erro (nesse ponto a mensagem de erro já ocorreu) eu apenas fecho... que o usuario
        //vai tentar novamente ...
        return false;
    }

    return true;
}

bool IDE::salvarEFecharAbas(bool salvar_alteracoes, bool fechar)
{
    for(int index=genDoc.tamanho()-1; index>=0; index--)
    {
        Documento *doc = genDoc[index];

        bool sujo = true; //se nao for para fechar então deve salvar incondicionamente

        if(fechar) // mas se for fechar todos entao verifica se está sujo
            sujo = doc->isSujo();

        if(sujo)
        {

            //Seta a tab index como a atual...
            setAbaAtual(index);

            //Seta o foco no edit...
            doc->setFocus();

            if(salvar_alteracoes)
            {
                switch(mostrarSalvarAlteracao())
                {
                    case QMessageBox::Cancel:
                    {
                        return false;
                    }
                    break;
                    case QMessageBox::Save:
                    {
                        if(!salvarAba(doc))
                            return false;
                    }
                    break;
                }
            }
            else
            {
                if(!salvarAba(doc))
                    return false;
            }

        }

        //Fecha remove a aba se for o caso
        if(fechar)
            removeAba(index, doc);
    }

    return true;
}

void IDE::gravarConfiguracoes()
{
    //Gravar Configuracoes Menu Ver
    gravarConfiguracoesMenuVer();

    //Gravar Configurações Fonte
    gravarConfiguracoesFonte();
}

void IDE::acaoSair()
{
    this->close();
}

void IDE::acaoSalvar()
{
    //pega o index do tab atual
    int index = getAbaAtual();

    //Pega o edit da hashtable
    Documento* doc = genDoc.procurar(index);

    QString fileName;

    bool salvar_como = false;

    if(!doc->isAberto())
    {
        fileName = mostrarSalvarArquivo(doc->getCaminhoCompleto());
        salvar_como = true;
    }
    else
        fileName = doc->getCaminhoCompleto();

    //Se estiver vazia não salva nada...
    if(fileName.isEmpty())
        return;

    salvarDocumento(doc, fileName, index, salvar_como);
}

void IDE::acaoSalvarComo()
{
    //pega o index do tab atual
    int index = this->ui->tabWidgetArquivos->currentIndex();

    //Pega o edit da hashtable
    Documento* doc = genDoc.procurar(index);

    //A onde salvar
    QString fileName = mostrarSalvarArquivo();

    //Se estiver vazia não salva nada...
    if(fileName.isEmpty())
        return;

    salvarDocumento(doc, fileName, index, true);

}

void IDE::salvarDocumento(Documento *document, QString &fileName, int index, bool salvar_como)
{
    bool result = gravarDocumento(document,fileName);
    if(!result)
        return;
    else
        genReabrir.atualizar(fileName);

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
    Documento* doc = genDoc.procurar(index);

    if(!doc->isSujo())
    {

        //poem o texto no lugar
        QString text = this->ui->tabWidgetArquivos->tabText(index);
        text+="*";
        this->ui->tabWidgetArquivos->setTabText(index, text);
        doc->sujou();
        configurarFonteEditor();
    }
}

void IDE::acaoHabilitarNumeroLinha(bool checked)
{
    EditorCodigo::setLineNumber(checked);

    //pega o index do tab atual
    int index = this->ui->tabWidgetArquivos->currentIndex();

    //Pega o edit da hashtable
    Documento* doc = genDoc.procurar(index);

    //Repintar o edit
    doc->repintarEditor();
}

void IDE::acaoHabilitarBarraFerramentas(bool checked)
{
    if(checked)
        this->ui->toolBar->show();
    else
        this->ui->toolBar->hide();

    ver_barra_ferramentas = checked;
}

void IDE::acaoHabilitarBarraStatus(bool checked)
{
    if(checked)
        this->ui->statusBar->show();
    else
        this->ui->statusBar->hide();

    ver_barra_status = checked;
}

void IDE::breakpoint(int line, bool checked)
{
    qDebug()<<line<<", "<<checked;
}

void IDE::mudouAbaAtual(int index)
{
    //Pega o edit da hashtable
    Documento* doc = genDoc.procurar(index);

    if(doc!=NULL)
    {
        //Repintar o edit
        doc->repintarEditor();
        doc->setFonte(familia_fonte, tamanho_fonte);
    }
}

void IDE::menuReabrirClicou(QString caminho)
{
    if(!caminho.isEmpty())
        abrirDocumento(caminho);
    else
        msgErroAbrir();
}

void IDE::acaoHabilitarFuncoes(bool checked)
{
    if(checked)
        this->ui->groupFuncoes->show();
    else
        this->ui->groupFuncoes->hide();

    //Salva o estado de Funcoes para ser gravado posteriormente
    ver_funcoes = checked;
}

void IDE::acaoHabilitarDebug(bool checked)
{
    if(checked)
        this->ui->tabDebug->show();
    else
        this->ui->tabDebug->hide();
    //Salva o estado de Debugger para ser gravado posteriormente
    ver_debugger = checked;
}

void IDE::acaoHabilitarExecProg(bool checked)
{
    if(checked)
        this->ui->tabgadget->show();
    else
        this->ui->tabgadget->hide();

    //Salva o estado de ExecProg para ser gravado posteriormente
    ver_exec_prog = checked;
}

void IDE::botaoFecharTabClicado()
{
    acaoFechar(genDoc.posicao(QObject::sender()));
}

void IDE::botaoMaisTabClicado()
{
    acaoNovo();
}

void IDE::reiniciarInterfaceClicado()
{
    //Funções...
    ver_funcoes = true;
    this->ui->actionFuncoes->setChecked(ver_funcoes);

    //Debug
    ver_debugger = true;
    this->ui->actionDebugger->setChecked(ver_debugger);

    //Debug
    ver_exec_prog = true;
    this->ui->actionExecProg->setChecked(ver_exec_prog);
}

void IDE::proximoDocumento()
{
    int index = getAbaAtual();
    if(++index >= genDoc.tamanho())
    {
        index = 0;
    }
    setAbaAtual(index);
}

void IDE::anteriroDocumento()
{
    int index = getAbaAtual();
    if(--index <= 0)
    {
        index = genDoc.tamanho()-1;
    }
    setAbaAtual(index);
}

void IDE::salvarTodosDocumentos()
{
    salvarEFecharAbas(false, false);
}

void IDE::fecharTodosDocumentos()
{
    salvarEFecharAbas();
}

void IDE::copiarDocumento()
{
    Documento* doc = genDoc.procurar(getAbaAtual());
    doc->copiar();
}

void IDE::colarDocumento()
{
    Documento* doc = genDoc.procurar(getAbaAtual());
    doc->colar();
}

void IDE::recortarDocumento()
{
    Documento* doc = genDoc.procurar(getAbaAtual());
    doc->recortar();
}

void IDE::menuEditarClicado()
{

    Documento* doc = genDoc.procurar(getAbaAtual());

    //Habilitar Ctrl+c se tiver texto selecionado
    if(doc->isTextoSelecionado())
        this->ui->menuEditar->actions().at(0)->setEnabled(true);
    else
        this->ui->menuEditar->actions().at(0)->setEnabled(false);

    //Habilitar Ctrl+v se tiver texto copiado...
    if(doc->isColarDisponivel())
        this->ui->menuEditar->actions().at(1)->setEnabled(true);
    else
        this->ui->menuEditar->actions().at(1)->setEnabled(false);

    //Habilitar Desfazer
    if(doc->isDesfazerDisponivel())
        this->ui->menuEditar->actions().at(4)->setEnabled(true);
    else
        this->ui->menuEditar->actions().at(4)->setEnabled(false);

    //Habilitar Refazer
    if(doc->isRefazerDisponivel())
        this->ui->menuEditar->actions().at(5)->setEnabled(true);
    else
        this->ui->menuEditar->actions().at(5)->setEnabled(false);

}

void IDE::desfazerDocumento()
{
    Documento* doc = genDoc.procurar(getAbaAtual());
    doc->desfazer();
}

void IDE::refazerDocumento()
{
    Documento* doc = genDoc.procurar(getAbaAtual());
    doc->refazer();
}

void IDE::duplicarLinhar()
{
    Documento* doc = genDoc.procurar(getAbaAtual());
    doc->duplicarLinha();
}

void IDE::menuArquivoClicado()
{
    //Se não tiver reabrir... desabilita o menu
    if(genDoc.tamanho()>0)
        this->ui->menuArquivo->actions().at(3)->setEnabled(true);
    else
        this->ui->menuArquivo->actions().at(3)->setEnabled(false);
}

void IDE::configurarFonteEditor()
{
    Documento* doc = genDoc.procurar(getAbaAtual());

    doc->setFonte(familia_fonte,tamanho_fonte);
}

void IDE::aumentarFonte()
{
    //Não Fica Maior que 72
    if(tamanho_fonte<72)
    {
        if(tamanho_fonte<12)
            tamanho_fonte++;
        else
            tamanho_fonte+=2;

        configurarFonteEditor();
    }
}

void IDE::diminuirFonte()
{
    //Não Fica menor que 6
    if(tamanho_fonte>7)
    {
        if(tamanho_fonte>=12)
            tamanho_fonte--;
        else
            tamanho_fonte-=2;

        configurarFonteEditor();
    }
}

void IDE::reiniciarFonte()
{
    tamanho_fonte = 9;
    familia_fonte = "sans-serif";

    configurarFonteEditor();
}

void IDE::fonteClicado()
{
    QString temp = familia_fonte;
    FonteDialog fonte(&temp, this);

    fonte.setFixedSize(fonte.size());

    if(fonte.exec()==QDialog::Accepted&&temp!=familia_fonte)
    {
        familia_fonte = temp;
        configurarFonteEditor();
    }
}

void IDE::irParaClicado()
{
    Documento* doc = genDoc.procurar(getAbaAtual());

    IrPara irPara(doc->getQuantidadeLinhas(), this);

    irPara.setFixedSize(irPara.size());

    if(irPara.exec()==QDialog::Accepted)
    {
        int linha = irPara.getNumeroLinha();
        doc->setPosicaoCursor(linha);
    }
}

void IDE::localizarClicado()
{
    genProc.setSubstituir(false);
    if(!genProc.isVisivel())
    {
        this->ui->actionExecProg->setChecked(true);
    }
    genProc.mostrar();
}

void IDE::substituirClicado()
{
    genProc.setSubstituir(true);
    if(!genProc.isVisivel())
    {
        this->ui->actionExecProg->setChecked(true);
    }
    genProc.mostrar();
}

void IDE::localizarProximoClicado()
{
    if(genProc.isPalavraProcuradaVazia())
    {
        genProc.setSubstituir(true);
        if(!genProc.isVisivel())
        {
            this->ui->actionExecProg->setChecked(true);
        }
        genProc.mostrar();
    }
    else
        genProc.localizar();
}

void IDE::localizarAnteriroClicado()
{
    if(genProc.isPalavraProcuradaVazia())
    {
        genProc.setSubstituir(true);
        if(!genProc.isVisivel())
        {
            this->ui->actionExecProg->setChecked(true);
        }
        genProc.mostrar();
    }
    else
        genProc.localizarAnterior();
}

