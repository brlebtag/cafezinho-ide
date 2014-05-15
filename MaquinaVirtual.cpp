#include "MaquinaVirtual.h"
#include "Instrucao.h"

MaquinaVirtual::MaquinaVirtual(QObject *parent) :
    QObject(parent), memoria(100)
{
    reiniciar();
}

MaquinaVirtual::~MaquinaVirtual()
{
    //remove todas as instruções criadas...
    try
    {
        for(int i=0; i<codigo.size(); ++i)
        {
           delete codigo[i];
        }

        for(int i=0; i<rotulo.size(); ++i)
        {
            delete rotulo[i];
        }
    }
    catch(exception &e)
    {

    }
}


void MaquinaVirtual::reiniciar()
{
    pc = 0;
    pp = 0;
    eax = 0;
    ebx = 0;
    ecx = 0;
    edx = 0;
    bp = 0;
    er = 0;
    pg = 0;
    bf = false;
    sf = false;
    ef = false;
    erf = false;
    execute = true;
    tp = false;
    qtdChamadasFuncao = 0;
    sinc_passo = true;
}

void MaquinaVirtual::msgErro(QString _err)
{
    CompInfo::err()<<_err;
}

void MaquinaVirtual::executar()
{
    emit comecar_execucao();

    while(execute&&(!erf))
    {
        try
        {
            codigo[pc]->execute(*this);
        }
        catch(exception &e)
        {
            //Não reporta erro só reportar embaixo mesmo... para não aparecer a mensagem x2
        }
        if(pc<0||pc>=codigo.size()||erf)
        {
            if(!tp)
            {
                CompInfo::err()<<"[SISTEMA] PROGRAMA ACABOU DE FORMA INESPERADA\n";
                erf = true;
            }
        }
    }

    emit terminou_execucao(!erf);
}

void MaquinaVirtual::parar()
{
    execute = false;
}

void MaquinaVirtual::passo()
{
    if(execute&&(!erf))
    {
        try
        {
            codigo[pc]->execute(*this);
        }
        catch(...)
        {
             //Não reporta erro só reportar embaixo mesmo... para não aparecer a mensagem x2
        }
        if(pc<0||pc>=codigo.size()||erf)
        {
            CompInfo::err()<<"[SISTEMA] PROGRAMA ACABOU DE FORMA INESPERADA\n";
            erf = true;
        }
    }
}

void MaquinaVirtual::escreveInt(int c)
{
    if(!this->erf)
        CompInfo::out()<<c;
}

void MaquinaVirtual::escreveChar(char c)
{
    if(!this->erf)
        CompInfo::out()<<c;
}

void MaquinaVirtual::escreveDouble(double c)
{
    if(!this->erf)
        CompInfo::out()<<c;
}

void MaquinaVirtual::escrevePalavra(QString *palavra)
{
    if(!this->erf)
        CompInfo::out()<<palavra;
}

int MaquinaVirtual::leInt()
{
    CompInfo::modoEntrada();
    CompInfo::inst()->mutexIO.lock();
    CompInfo::inst()->waitIO.wait(&(CompInfo::inst()->mutexIO));
    CompInfo::inst()->mutexIO.unlock();
    return CompInfo::inst()->entrada.toInt();
}

char MaquinaVirtual::leChar()
{
    CompInfo::modoEntrada();
    CompInfo::inst()->mutexIO.lock();
    CompInfo::inst()->waitIO.wait(&(CompInfo::inst()->mutexIO));
    CompInfo::inst()->mutexIO.unlock();
    return CompInfo::inst()->entrada[0].toLatin1();
}

double MaquinaVirtual::leDouble()
{
    CompInfo::modoEntrada();
    CompInfo::inst()->mutexIO.lock();
    CompInfo::inst()->waitIO.wait(&(CompInfo::inst()->mutexIO));
    CompInfo::inst()->mutexIO.unlock();
    return CompInfo::inst()->entrada.toDouble();
}

void MaquinaVirtual::sistema(Sistema::Comando comando)
{
    switch(comando)
    {
        case Sistema::LIMPAR:
        {
            emit limpar_terminal();
        }
        break;
        case Sistema::NOVA_LINHA:
        {
            CompInfo::appendTexto("</br>");
        }
        break;
    }
}

void MaquinaVirtual::empilha_chamada()
{
    //indiferente se tiver continuar/proximo/entrar
    //eu devo criar e remover variaveis porém esse processo fica invisivel ao usuario...
    //com genVar->setVisibilidade(false); - Eu crio as variaveis mas não insiro na GUI.
    emit empilha_quadro_debug();

    //Eu preciso sincronizar está parte...
    CompInfo::inst()->mutexSincPasso.lock();
    CompInfo::inst()->waitSincPasso.wait(&CompInfo::inst()->mutexSincPasso);
    CompInfo::inst()->mutexSincPasso.unlock();

    if(statusExec == StatusExec::PROXIMA)
    {
        ++qtdChamadasFuncao;
        sinc_passo = false;
        if(qtdChamadasFuncao>=1)
        {
            emit desabilitar_botoes_debug();
        }
    }
}

void MaquinaVirtual::desempilha_chamada()
{

    //indiferente se tiver continuar/proximo/entrar
    //eu devo criar e remover variaveis porém esse processo fica invisivel ao usuario...
    //com genVar->setVisibilidade(false); - Eu crio as variaveis mas não insiro na GUI.
    emit desempilha_quadro_debug();

    //Eu preciso sincronizar está parte...
    CompInfo::inst()->mutexSincPasso.lock();
    CompInfo::inst()->waitSincPasso.wait(&CompInfo::inst()->mutexSincPasso);
    CompInfo::inst()->mutexSincPasso.unlock();

    if(statusExec == StatusExec::PROXIMA)
    {
        if(--qtdChamadasFuncao<=0)
        {
            sinc_passo = true;
        }
    }
}

void MaquinaVirtual::proximo()
{
    statusExec = StatusExec::PROXIMA;
    qtdChamadasFuncao = 0;
    sinc_passo = true;
}

void MaquinaVirtual::entrar()
{
    statusExec = StatusExec::ENTRAR;
    sinc_passo = true;
}

void MaquinaVirtual::continuar()
{
    statusExec = StatusExec::CONTINUAR;
    sinc_passo = false;
}

void MaquinaVirtual::empilha_variavel(No *no, int offset, int profundidade, No *pno)
{
    //indiferente se tiver continuar/proximo/entrar
    //eu devo criar e remover variaveis porém esse processo fica invisivel ao usuario...
    //com genVar->setVisibilidade(false); - Eu crio as variaveis mas não insiro na GUI.

    //Não posso tratar aki diretamente tem que ser via IDE por que no Qt não da para alterar a interface grafica
    //em outra thread!!!!

    //Pega o endereço corredo da variavel...

    if(profundidade>0)
        offset = bp.toInt() + offset; //Se não for variavel global: Base Pilha + Offset
    else
        offset = pg.toInt() + offset;// Se for global: Ponteiro Global + Offset

    //Se foi ponteiro então offset contem o endereço do ponteiro e o ponteiro contem o endereço do vetor...
    if(pno!=NULL)
        offset = this->memoria[offset].toInt(); //carrego o endereço que o ponteiro possui...

    emit empilha_variavel_debug(no, offset, pno);

    //Eu preciso sincronizar está parte...
    CompInfo::inst()->mutexSincPasso.lock();
    CompInfo::inst()->waitSincPasso.wait(&CompInfo::inst()->mutexSincPasso);
    CompInfo::inst()->mutexSincPasso.unlock();
}

void MaquinaVirtual::desempilha_variavel(No *no)
{
    //indiferente se tiver continuar/proximo/entrar
    //eu devo criar e remover variaveis porém esse processo fica invisivel ao usuario...
    //com genVar->setVisibilidade(false); - Eu crio as variaveis mas não insiro na GUI.

    //Não posso tratar aki diretamente tem que ser via IDE por que no Qt não da para alterar a interface grafica
    //em outra thread!!!!
    emit desempilha_variavel_debug(no);

    //Eu preciso sincronizar está parte...
    CompInfo::inst()->mutexSincPasso.lock();
    CompInfo::inst()->waitSincPasso.wait(&CompInfo::inst()->mutexSincPasso);
    CompInfo::inst()->mutexSincPasso.unlock();
}

void MaquinaVirtual::atualizarVariaveis()
{
    // é preciso que continua empilhado/desempilhando variavel se não tiver no sinc_passo mas não precisa ficar atualizando
    // senão pode sobrecarregar...

    if(sinc_passo)
    {
        emit atualizar_variavel();

        //Eu preciso sincronizar está parte...
        CompInfo::inst()->mutexSincPasso.lock();
        CompInfo::inst()->waitSincPasso.wait(&CompInfo::inst()->mutexSincPasso);
        CompInfo::inst()->mutexSincPasso.unlock();
    }
}

void MaquinaVirtual::sincronizar_passo(int linha)
{
    bool contem = CompInfo::isBreakPoint(linha);

    if(sinc_passo || contem)
    {
        emit mudou_instrucao(linha);
        CompInfo::inst()->mutexSincPasso.lock();
        CompInfo::inst()->waitSincPasso.wait(&CompInfo::inst()->mutexSincPasso);
        CompInfo::inst()->mutexSincPasso.unlock();
    }
}
