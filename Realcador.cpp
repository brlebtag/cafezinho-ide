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

    //Significado dos estados:
    // 0 : não está num bloco com comentarios
    // 1 : está num bloco com comentarios..
    //Eu salvo está informação para controlar os comentarios que ocupam varias linhas
    setCurrentBlockState(0);

    int comecoIndice = 0;
    //Verifico se o bloco anterior está dentro de um bloco com comentario senão tiver eu procuro
    //Se neste bloco possui o inicio do comentario
    if (previousBlockState() != 1)
             comecoIndice = comecoComentario.indexIn(text);

    while (comecoIndice >= 0)
    {
        //Procuro pelo fim do comentario depois de comecoIndice...
        int terminoIndice = terminoComentario.indexIn(text, comecoIndice);

        //Contar o tamanho do comentario...
        int tamanhoComentario = 0;

        if(terminoIndice == -1)
        {
            setCurrentBlockState(1); //marco que este bloco é um comentario;
            tamanhoComentario = text.length() - comecoIndice;//faço o calculo do tamanho do comentario
        }
        else
        {
            //faço o calculo do tamanho do comentario: fim - inicio + sizeof(*/)
            tamanhoComentario = terminoIndice - comecoIndice + terminoComentario.matchedLength();
        }
        //coloco o formatoComentario começando apartir de comecoIndice até comecoIndice+tamanhoComentario
        setFormat(comecoIndice, tamanhoComentario, formatoComentario);

        //Aplico a busca novamente por começo comentario... talvez pode ter mais comentarios de multilinhas na mesma linha
        comecoIndice = comecoComentario.indexIn(text, comecoIndice + tamanhoComentario);
    }
}
