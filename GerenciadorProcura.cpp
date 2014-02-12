#include "GerenciadorProcura.h"

GerenciadorProcura::GerenciadorProcura(QObject *parent) :
    QObject(parent)
{
    visivel = false;
    substituir = false;
    palavraInteira = false;
    ignorarMaisculo = false;
}

GerenciadorProcura::~GerenciadorProcura()
{
    if(visivel)
    {
        delete widget;
    }
}

bool GerenciadorProcura::isVisivel()
{
    return this->visivel;
}

void GerenciadorProcura::setVisivel(bool visivel)
{
    this->visivel = visivel;
}

QWidget *GerenciadorProcura::getWidget()
{
    return this->widget;
}

QPushButton *GerenciadorProcura::getBotaoFechar()
{
    return this->botaoFechar;
}

void GerenciadorProcura::mostrar()
{
    if(!visivel)
    {

        this->widget = criarAba();
        this->widget->setSubstituir(substituir);
        visivel = true;
    }
}

void GerenciadorProcura::setTabWidget(QTabWidget *tabWidget)
{
    this->tabWidget = tabWidget;
}

void GerenciadorProcura::setEditor(QPlainTextEdit *edit)
{
    this->edit = edit;
    connect(edit, SIGNAL(selectionChanged()), this, SLOT(mudouSelecao()));
}

void GerenciadorProcura::substituirClicado()
{
    //Pega o cursor Atual
    QTextCursor cursor(edit->textCursor());

    //Se tiver texto selecionado... inseri por cima...
    if(cursor.hasSelection())
        cursor.insertText(palavraSubstituir);

    //Chama localizar para procurar a proxima
    localizar();
}

void GerenciadorProcura::substiturirTudoClicado()
{
    QTextCursor cursor(edit->document());
    QTextDocument *documento = edit->document();

    int flag = 0;

    //Gera as flags necessarias na busca...
    if(!ignorarMaisculo)
        flag = (int) (flag | QTextDocument::FindCaseSensitively);
    if(palavraInteira)
        flag = (int) (flag | QTextDocument::FindWholeWords);

    while (!cursor.isNull() && !cursor.atEnd())
    {
        cursor = documento->find(palavraProcurada, cursor, (enum QTextDocument::FindFlag)(flag));

        if (!cursor.isNull())
        {
            cursor.insertText(palavraSubstituir);
        }
    }

    QList<QTextEdit::ExtraSelection> extraSelections;
    edit->setExtraSelections(extraSelections);//limpar as extra selections
}

void GerenciadorProcura::ignorarMaisculoClicado(bool checked)
{
    ignorarMaisculo = checked;
}

void GerenciadorProcura::palavraInteiraClicado(bool checked)
{
    palavraInteira = checked;
}

void GerenciadorProcura::mudouSelecao()
{
    if(visivel)
    {
        QList<QTextEdit::ExtraSelection> extraSelection;
        edit->setExtraSelections(extraSelection);
    }
}

void GerenciadorProcura::setSubstituir(bool substituir)
{
    this->substituir = substituir;
    if(visivel)
        this->widget->setSubstituir(substituir);
    atualizarInterface();
}

void GerenciadorProcura::atualizarInterface()
{
    setTituloAba(getTituloAba());
}

QPushButton *GerenciadorProcura::criarBotaoFecharAba(QWidget* pai)
{
    //Cria um botao
    QPushButton *button = new QPushButton(pai);

    //Seta o Icon do botão
    button->setIcon(*(new QIcon(":/fechar.png")));

    //Seta o tamanho maximo
    button->setFixedWidth(20);
    button->setFixedHeight(20);

    //Conecta o sinal para receber quando este for clicado
    connect(button,SIGNAL(clicked()),this,SLOT(esconder()));

    return button;
}

Procurar *GerenciadorProcura::criarAba()
{
    //Criar a aba..
    Procurar* tab = new Procurar();

    //colocar os conectores...

    connect(tab,SIGNAL(localizarClicado()),this, SLOT(localizar()));
    connect(tab, SIGNAL(localizarAnteriorClicado()), this, SLOT(localizarAnterior()));
    connect(tab, SIGNAL(substituirClicado()), this, SLOT(substituirClicado()));
    connect(tab, SIGNAL(substituirTudoClicado()), this, SLOT(substiturirTudoClicado()));
    connect(tab, SIGNAL(palavraInteiraMarcado(bool)), this, SLOT(palavraInteiraClicado(bool)));
    connect(tab, SIGNAL(ignorarMaisculaMarcado(bool)), this, SLOT(ignorarMaisculoClicado(bool)));
    connect(tab, SIGNAL(mudouPalavraProcurada(QString)), this, SLOT(atualizarPalavraProcurada(QString)));
    connect(tab, SIGNAL(mudouPalavraSubstituir(QString)), this, SLOT(atualizarPalavraSubstituir(QString)));

    //Inseri a aba...
    int id = tabWidget->addTab(tab, getTituloAba());

    //seta a nova aba como atual
    tabWidget->setCurrentWidget(tab);

    //Criar botao fechar
    this->botaoFechar = criarBotaoFecharAba(tab);

    //Inseri o botao
    tabWidget->tabBar()->setTabButton(id, QTabBar::RightSide, (QWidget*) (botaoFechar));

    return tab;
}

QString GerenciadorProcura::getTituloAba()
{
    if(substituir)
    {
        return "Localizar e Substituir";
    }

    return "Localizar";
}

void GerenciadorProcura::setTituloAba(QString titulo)
{
    tabWidget->setTabText(indiceAba(), titulo);
}

int GerenciadorProcura::indiceAba()
{
    return tabWidget->indexOf(widget);
}

void GerenciadorProcura::mudouEditor(QPlainTextEdit *edit)
{
    this->edit = edit;
}

void GerenciadorProcura::esconder()
{
    if(visivel)
    {
        QList<QTextEdit::ExtraSelection> extraSelections;
        edit->setExtraSelections(extraSelections);//limpar as extra selections... ao sair da janela procurar
        visivel = false;
        delete widget;
    }
}

void GerenciadorProcura::localizar()
{
    //Faz o documento receber o foco para poder pegar o cursor...
    edit->setFocus();
    //Criar um cursor apartir do começo do documento
    QTextCursor cursorComeco(edit->document());

    //Criar um cursor apartir do cursor atual
    QTextCursor cursorAtual(edit->textCursor());

    //Criar um cursor para percorrer o arquivo apartir do atual
    QTextCursor cursorMover(cursorAtual);

    //Pega o documento
    QTextDocument *documento = edit->document();

    //Criar um lista com as extras selecoes...
    QList<QTextEdit::ExtraSelection> extraSelections;

    bool first = true;

    int flag = 0;

    //Gera as flags necessarias na busca...
    if(!ignorarMaisculo)
        flag = (int) (flag | QTextDocument::FindCaseSensitively);
    if(palavraInteira)
        flag = (int) (flag | QTextDocument::FindWholeWords);

    //Percorre apartir do cursor atual até o final procurando a palavra...
    while(!cursorMover.isNull() && !cursorMover.atEnd())
    {
        if(flag != 0)
            cursorMover = documento->find(palavraProcurada, cursorMover, (enum QTextDocument::FindFlag) flag);
        else
            cursorMover = documento->find(palavraProcurada, cursorMover);

        if (!cursorMover.isNull())
        {
            //Se por a primeira busca então essa palavra é selecionada...
            if(first)
            {
                edit->setTextCursor(cursorMover); //poem o cursor atual como onde o cursor deve estar
                first = false;
            }
            //Criar as marçẽos amarelas nas palavras iguais a procurada
            QTextEdit::ExtraSelection selection;
            QColor lineColor = QColor(Qt::yellow).lighter(160);
            selection.format.setBackground(lineColor);
            selection.format.setProperty(QTextFormat::FullWidthSelection, false);
            selection.cursor = cursorMover;
            extraSelections.append(selection);
        }
    }
    //agora aplica a busca do começo para o cursor atual
    while(!cursorComeco.isNull() && (cursorComeco < cursorAtual))
    {
        if(flag != 0)
            cursorComeco = documento->find(palavraProcurada, cursorComeco, (enum QTextDocument::FindFlag)(flag));
        else
            cursorComeco = documento->find(palavraProcurada, cursorComeco);

        //Se não encontrou antes então procurar agora e a seleciona se for encontrada
        if (!cursorComeco.isNull())
        {
            if(first)
            {
                edit->setTextCursor(cursorComeco); //poem o cursor atual como onde o cursor deve estar
                first = false;
            }
            //Criar as marçẽos amarelas nas palavras iguais a procurada
            QTextEdit::ExtraSelection selection;
            QColor lineColor = QColor(Qt::yellow).lighter(160);
            selection.format.setBackground(lineColor);
            selection.format.setProperty(QTextFormat::FullWidthSelection, false);
            selection.cursor = cursorComeco;
            extraSelections.append(selection);
        }
    }

    // poem as selecoes no documento
    edit->setExtraSelections(extraSelections);

}

void GerenciadorProcura::localizarAnterior()
{
    //Faz o documento receber o foco para poder pegar o cursor...
    edit->setFocus();

    //Criar um cursor apartir do cursor atual
    QTextCursor cursorAtual(edit->textCursor());

    //Criar um cursor para caminhar
    QTextCursor cursorMover(cursorAtual);

    //Pega o documento
    QTextDocument *documento = edit->document();

    //Criar um cursor e posiciona no final do documento...
    QTextBlock ultimoBloco = documento->lastBlock();
    QTextCursor cursorFim(ultimoBloco);
    cursorFim.movePosition(QTextCursor::EndOfLine,QTextCursor::MoveAnchor);

    //Criar um lista com as extras selecoes...
    QList<QTextEdit::ExtraSelection> extraSelections;

    bool first = true;

    //Marca para fazer a busca de trás para frente
    int flag = QTextDocument::FindBackward;

    //Gera as flags necessarias na busca...
    if(!ignorarMaisculo)
        flag = (int) (flag | QTextDocument::FindCaseSensitively);
    if(palavraInteira)
        flag = (int) (flag | QTextDocument::FindWholeWords);

    //Percorre apartir do cursor atual até o final procurando a palavra...
    while(!cursorMover.isNull() && !cursorMover.atStart())
    {
        if(flag != 0)
            cursorMover = documento->find(palavraProcurada, cursorMover, (enum QTextDocument::FindFlag)(flag));
        else
            cursorMover = documento->find(palavraProcurada, cursorMover);

        if (!cursorMover.isNull())
        {
            //Se por a primeira busca então essa palavra é selecionada...
            if(first)
            {
                edit->setTextCursor(cursorMover); //poem o cursor atual como onde o cursor deve estar
                first = false;
            }
            //Criar as marçẽos amarelas nas palavras iguais a procurada
            QTextEdit::ExtraSelection selection;
            QColor lineColor = QColor(Qt::yellow).lighter(160);
            selection.format.setBackground(lineColor);
            selection.format.setProperty(QTextFormat::FullWidthSelection, false);
            selection.cursor = cursorMover;
            extraSelections.append(selection);
        }
    }
    //agora aplica a busca do começo para o cursor atual
    while(!cursorFim.isNull() && (cursorFim > cursorAtual))
    {
        if(flag != 0)
            cursorFim = documento->find(palavraProcurada, cursorFim, (enum QTextDocument::FindFlag) flag);
        else
            cursorFim = documento->find(palavraProcurada, cursorFim);

        //Se não encontrou antes então procurar agora e a seleciona se for encontrada
        if (!cursorFim.isNull())
        {
            if(first)
            {
                edit->setTextCursor(cursorFim); //poem o cursor atual como onde o cursor deve estar
                first = false;
            }
            //Criar as marçẽos amarelas nas palavras iguais a procurada
            QTextEdit::ExtraSelection selection;
            QColor lineColor = QColor(Qt::yellow).lighter(160);
            selection.format.setBackground(lineColor);
            selection.format.setProperty(QTextFormat::FullWidthSelection, false);
            selection.cursor = cursorFim;
            extraSelections.append(selection);
        }
    }

    // poem as selecoes no documento
    edit->setExtraSelections(extraSelections);
}

void GerenciadorProcura::atualizarPalavraProcurada(QString palavra)
{
    palavraProcurada = palavra;
}

void GerenciadorProcura::atualizarPalavraSubstituir(QString palavra)
{
    palavraSubstituir = palavra;
}
