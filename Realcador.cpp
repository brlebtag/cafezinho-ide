#include "Realcador.h"

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

    listaPalavrasChaves<<"\\bcar\\b"<<"\\bint\\b"<<"\\bprograma\\b"
                       <<"\\bretorne\\b"<<"\\bleia\\b"<<"\\bescreva\\b"
                       <<"\\bnovalinha\\b"<<"\\bse\\b"<<"\\bentao\\b"
                       <<"\\bsenao\\b"<<"\\benquanto\\b"<<"\\bexecute\\b"
                       <<"\\be\\b"<<"\\bou\\b";
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
    regra.padrao = QRegExp("\\\"[^\\\"]*\\\"");
    regra.formato = formatoPalavraLiteral;
    regrasRealce.append(regra);

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
