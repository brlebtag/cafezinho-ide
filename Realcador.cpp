#include "Realcador.h"

const int Realcador::QTD_SIMBOLOS = 6;

const char Realcador::simbolos [] = {'{', '}', '(',')', '[',']'};

Realcador::Realcador(QTextDocument *documento)
    : QSyntaxHighlighter(documento)
{
    RegrasRealce regra;

    formatoFuncao.setFontItalic(true);
    formatoFuncao.setForeground(Qt::blue);

    regra.padrao = QRegExp("\\b[A-Za-z0-9_]+(?=\\()");
    regra.formato = formatoFuncao;
    regrasRealce.append(regra);

    formatoPalavrasChaves.setForeground(Qt::darkBlue);
    formatoPalavrasChaves.setFontWeight(QFont::Bold);

    QStringList listaPalavrasChaves;

    listaPalavrasChaves<<"\\bcar\\b"<<"\\breal\\b"<<"\\bnulo\\b"<<"\\bint\\b"
                       <<"\\bretorne\\b"<<"\\bleia\\b"<<"\\bescreva\\b"
                       <<"\\bnovalinha\\b"<<"\\bse\\b"<<"\\bentao\\b"
                       <<"\\bsenao\\b"<<"\\benquanto\\b"<<"\\bexecute\\b"
                       <<"\\be\\b"<<"\\bou\\b"<<"\\bterminar\\b"<<"\\blimpar\\b";

    foreach (const QString &padrao, listaPalavrasChaves)
    {
        regra.padrao = QRegExp(padrao);
        regra.formato = formatoPalavrasChaves;
        regrasRealce.append(regra);
    }

    formatoCaracterLiteral.setForeground(Qt::darkRed);
    regra.padrao = QRegExp("\\'.\\'");
    regra.formato = formatoCaracterLiteral;
    regrasRealce.append(regra);

    formatoPalavraLiteral.setForeground(Qt::darkRed);
    //regra.padrao = QRegExp("\\\"[^\\\"]*\\\"");
    //regra.formato = formatoPalavraLiteral;
    //regrasRealce.append(regra);

    comecoComentario = QRegExp("/\\*");
    terminoComentario = QRegExp("\\*/");
    formatoComentario.setForeground(Qt::darkGreen);
}


void Realcador::highlightBlock(const QString &text)
{
    //Aplica as regras que estao em regrasRealce...
    foreach (const RegrasRealce &regra, regrasRealce)
    {
        //Gera uma expressão apartir de padrao...
        QRegExp expressao(regra.padrao);

        //Pega o indice da primeira ocorrencia... ou -1 se não encontrou...
        int indice = expressao.indexIn(text);

        //Enquanto existir regra naquele bloco de texto...
        while (indice >= 0)
        {
            //Pega o tamanho da palavra que foi combinada
            int tamanho = expressao.matchedLength();

            //Seta o formato naquela palavra encontrada...
            setFormat(indice, tamanho, regra.formato);

            //procura por outras palavras que estão na mesma linha...
            indice = expressao.indexIn(text, indice + tamanho);
        }
    }

    //Salvar parenteses, colchetes e chaves...
    bool comentario = false;
    bool palavra = false;
    bool charLit = false;

    DadoBlocoTexto* dado = new DadoBlocoTexto();

    int comecoPalavar = 0;

    if(previousBlockState()==1)
        comentario = true;

    int i =0;

    for(i=0; i<text.size(); ++i)
    {
        if(text[i]=='\"')
        {
            if(palavra)
            {
                setFormat(comecoPalavar, i - comecoPalavar+1, formatoPalavraLiteral);
                palavra = false;
                continue;
            }

            if(!palavra)
            {
                comecoPalavar = i;
                palavra = true;
            }

        }

        if(text[i]=='\'')
        {
            charLit = !charLit;
        }

        if(text[i]=='/'&&(i+1)<text.size()&&text[i+1]=='*')
            comentario = true;

        if(text[i]=='*'&&(i+1)<text.size()&&text[i+1]=='\\')
            comentario = false;

        if((!comentario)&&(!palavra)&&(!charLit))
        {
            for(int j=0; j<Realcador::QTD_SIMBOLOS; ++j)
            {
                if(text[i]==Realcador::simbolos[j])
                {
                    dado->inserir(Realcador::simbolos[j], i);
                }
            }
        }
    }

    if(palavra)
        setFormat(comecoPalavar, i - comecoPalavar, formatoPalavraLiteral);

    setCurrentBlockUserData(dado);

    setCurrentBlockState(0);

    int indiceComeco = 0;

    if(previousBlockState()!=1)
        indiceComeco = comecoComentario.indexIn(text);

    while(indiceComeco>=0)
    {
        int indiceFinal = terminoComentario.indexIn(text, indiceComeco);
        int tamanhoComentario;

        if(indiceFinal == -1)
        {
            setCurrentBlockState(1);
            tamanhoComentario = text.length() - indiceComeco;
        }
        else
        {
            tamanhoComentario = indiceFinal - indiceComeco + terminoComentario.matchedLength();
        }
        setFormat(indiceComeco, tamanhoComentario, formatoComentario);
        indiceComeco = comecoComentario.indexIn(text, indiceComeco + tamanhoComentario);
    }
}
