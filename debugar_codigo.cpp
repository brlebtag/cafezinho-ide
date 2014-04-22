#include "debugar_geracao.h"

using namespace TipoInstrucao;

void debug_codigo(MaquinaVirtual &vm)
{
    int i=1;
    for(QVector<Instrucao*>::iterator it = vm.codigo.begin(); it!= vm.codigo.end(); ++it, ++i)
    {
        imprime_instrucao(vm, (*it), i);
    }
}

void imprime_instrucao(MaquinaVirtual &vm, Instrucao * instrucao, int posicao)
{
    switch(instrucao->tipoInstucao())
    {
        case MOVE:
        {
            IMove *inst = dynamic_cast<IMove*>(instrucao);
            qDebug()<<posicao<<": mov "<<nome_reg(vm, inst->registrador1)<<", "<<nome_reg(vm, inst->registrador2);
        }
        break;
        case MOVE_IM:
        {
            IMoveIm *inst = dynamic_cast<IMoveIm*>(instrucao);
            qDebug()<<posicao<<": mov "<<nome_reg(vm, inst->registrador1)<<", "<<nome_reg(vm, inst->registrador2);
        }
        break;
        case ADC:
        {
            IAdc *inst = dynamic_cast<IAdc*>(instrucao);
            qDebug()<<posicao<<": adc "<<nome_reg(vm, inst->registrador)<<", "<<nome_reg(vm, inst->operando1)<<", "<<nome_reg(vm, inst->operando2);
        }
        break;
        case ADC_IM:
        {
            IAdcIm *inst = dynamic_cast<IAdcIm*>(instrucao);
            qDebug()<<posicao<<": adc "<<nome_reg(vm, inst->registrador)<<", "<<nome_reg(vm, inst->operando1)<<", "<<nome_reg(vm, inst->operando2);
        }
        break;
        case SUB:
        {
            ISub *inst = dynamic_cast<ISub*>(instrucao);
            qDebug()<<posicao<<": sub "<<nome_reg(vm, inst->registrador)<<", "<<nome_reg(vm, inst->operando1)<<", "<<nome_reg(vm, inst->operando2);
        }
        break;
        case SUB_IM:
        {
            ISubIm *inst = dynamic_cast<ISubIm*>(instrucao);
            qDebug()<<posicao<<": sub "<<nome_reg(vm, inst->registrador)<<", "<<nome_reg(vm, inst->operando1)<<", "<<nome_reg(vm, inst->operando2);
        }
        break;
        case MULT:
        {
            IMult *inst = dynamic_cast<IMult*>(instrucao);
            qDebug()<<posicao<<": mult "<<nome_reg(vm, inst->registrador)<<", "<<nome_reg(vm, inst->operando1)<<", "<<nome_reg(vm, inst->operando2);
        }
        break;
        case MULT_IM:
        {
            IMultIm *inst = dynamic_cast<IMultIm*>(instrucao);
            qDebug()<<posicao<<": mult "<<nome_reg(vm, inst->registrador)<<", "<<nome_reg(vm, inst->operando1)<<", "<<nome_reg(vm, inst->operando2);
        }
        break;
        case DIV:
        {
            IDiv *inst = dynamic_cast<IDiv*>(instrucao);
            qDebug()<<posicao<<": div "<<nome_reg(vm, inst->registrador)<<", "<<nome_reg(vm, inst->operando1)<<", "<<nome_reg(vm, inst->operando2);
        }
        break;
        case DIV_IM:
        {
            IDivIm *inst = dynamic_cast<IDivIm*>(instrucao);
            qDebug()<<posicao<<": div "<<nome_reg(vm, inst->registrador)<<", "<<nome_reg(vm, inst->operando1)<<", "<<nome_reg(vm, inst->operando2);
        }
        break;
        case CMP:
        {
            ICmp *inst = dynamic_cast<ICmp*>(instrucao);
            qDebug()<<posicao<<": cmp "<<nome_reg(vm, inst->operando1)<<", "<<nome_reg(vm, inst->operando2);
        }
        break;
        case CMP_IM:
        {
            ICmpIm *inst = dynamic_cast<ICmpIm*>(instrucao);
            qDebug()<<posicao<<": cmp "<<nome_reg(vm, inst->operando1)<<", "<<nome_reg(vm, inst->operando2);
        }
        break;
        case SALTO:
        {
            ISalto *inst = dynamic_cast<ISalto*>(instrucao);
            qDebug()<<posicao<<": si "<<inst->offset;
        }
        break;
        case SALTO_EQ:
        {
            ISaltoEq *inst = dynamic_cast<ISaltoEq*>(instrucao);
            qDebug()<<posicao<<": seq "<<inst->offset;
        }
        break;
        case SALTO_MAIOR:
        {
            ISaltoMaior *inst = dynamic_cast<ISaltoMaior*>(instrucao);
            qDebug()<<posicao<<": smq "<<inst->offset;
        }
        break;
        case SALTO_NAO_EQ:
        {
            ISaltoNaoEq *inst = dynamic_cast<ISaltoNaoEq*>(instrucao);
            qDebug()<<posicao<<": sne "<<inst->offset;
        }
        break;
        case SALTO_MAIOR_EQ:
        {
            ISaltoMaiorEq *inst = dynamic_cast<ISaltoMaiorEq*>(instrucao);
            qDebug()<<posicao<<": sme "<<inst->offset;
        }
        break;
        case SALTO_MENOR:
        {
            ISaltoMenor *inst = dynamic_cast<ISaltoMenor*>(instrucao);
            qDebug()<<posicao<<": sme "<<inst->offset;
        }
        break;
        case SALTO_MENOR_EQ:
        {
            ISaltoMenorEq *inst = dynamic_cast<ISaltoMenorEq*>(instrucao);
            qDebug()<<posicao<<": smeq "<<inst->offset;
        }
        break;
        case PARAR:
        {
            IParar *inst = dynamic_cast<IParar*>(instrucao);
            qDebug()<<posicao<<": parar";
        }
        break;
        case CHAMADA:
        {
            IChamada *inst = dynamic_cast<IChamada*>(instrucao);
            qDebug()<<posicao<<": inv "<<inst->offset;
        }
        break;
        case LEITURA_INT:
        {
            ILeituraInt *inst = dynamic_cast<ILeituraInt*>(instrucao);
            qDebug()<<posicao<<": lei "<<nome_reg(vm, inst->m);
        }
        break;
        case LEITURA_CAR:
        {
            ILeituraCar *inst = dynamic_cast<ILeituraCar*>(instrucao);
            qDebug()<<posicao<<": lec "<<nome_reg(vm, inst->m);
        }
        break;
        case LEITURA_REAL:
        {
            ILeituraReal *inst = dynamic_cast<ILeituraReal*>(instrucao);
            qDebug()<<posicao<<": ler "<<nome_reg(vm, inst->m);
        }
        break;
        case CARREGA:
        {
            ICarrega *inst = dynamic_cast<ICarrega*>(instrucao);
            qDebug()<<posicao<<": cp "<<nome_reg(vm, inst->registrador)<<", "<<inst->desl<<"["<<nome_reg(vm, inst->offset)<<"]";
        }
        break;
        case SALVA:
        {
            ISalva *inst = dynamic_cast<ISalva*>(instrucao);
            qDebug()<<posicao<<": sp "<<nome_reg(vm, inst->registrador)<<", "<<inst->desl<<"["<<nome_reg(vm, inst->offset)<<"]";
        }
        break;
        case E_BIT:
        {
            IEBit *inst = dynamic_cast<IEBit*>(instrucao);
            qDebug()<<posicao<<": e "<<nome_reg(vm, inst->registrador)<<", "<<nome_reg(vm, inst->operando1)<<", "<<nome_reg(vm, inst->operando2);
        }
        break;
        case E_BIT_IM:
        {
            IEBitIm *inst = dynamic_cast<IEBitIm*>(instrucao);
            qDebug()<<posicao<<": e "<<nome_reg(vm, inst->registrador)<<", "<<nome_reg(vm, inst->operando1)<<", "<<nome_reg(vm, inst->operando2);
        }
        break;
        case OU_BIT:
        {
            IOuBit *inst = dynamic_cast<IOuBit*>(instrucao);
            qDebug()<<posicao<<": ou "<<nome_reg(vm, inst->registrador)<<", "<<nome_reg(vm, inst->operando1)<<", "<<nome_reg(vm, inst->operando2);
        }
        break;
        case OU_BIT_IM:
        {
            IOuBitIm *inst = dynamic_cast<IOuBitIm*>(instrucao);
            qDebug()<<posicao<<": ou "<<nome_reg(vm, inst->registrador)<<", "<<nome_reg(vm, inst->operando1)<<", "<<nome_reg(vm, inst->operando2);
        }
        break;
        case XOR_BIT:
        {
            IXorBit *inst = dynamic_cast<IXorBit*>(instrucao);
            qDebug()<<posicao<<": xor "<<nome_reg(vm, inst->registrador)<<", "<<nome_reg(vm, inst->operando1)<<", "<<nome_reg(vm, inst->operando2);
        }
        break;
        case XOR_BIT_IM:
        {
            IXorBitIm *inst = dynamic_cast<IXorBitIm*>(instrucao);
            qDebug()<<posicao<<": xor "<<nome_reg(vm, inst->registrador)<<", "<<nome_reg(vm, inst->operando1)<<", "<<nome_reg(vm, inst->operando2);
        }
        break;
        case SHIFT_DIR:
        {
            IShiftDir *inst = dynamic_cast<IShiftDir*>(instrucao);
            qDebug()<<posicao<<": shd "<<nome_reg(vm, inst->registrador)<<", "<<nome_reg(vm, inst->operando1)<<", "<<nome_reg(vm, inst->operando2);
        }
        break;
        case SHIFT_ESQ:
        {
            IShiftEsq *inst = dynamic_cast<IShiftEsq*>(instrucao);
            qDebug()<<posicao<<": she "<<nome_reg(vm, inst->registrador)<<", "<<nome_reg(vm, inst->operando1)<<", "<<nome_reg(vm, inst->operando2);
        }
        break;
        case LIG_MAIOR_QUE:
        {
            ILigMaiorQ *inst = dynamic_cast<ILigMaiorQ*>(instrucao);
            qDebug()<<posicao<<": lmq "<<nome_reg(vm, inst->registrador)<<", "<<nome_reg(vm, inst->operando1)<<", "<<nome_reg(vm, inst->operando2);
        }
        break;
        case LIG_MAIOR_QUE_IM:
        {
            ILigMaiorQIm *inst = dynamic_cast<ILigMaiorQIm*>(instrucao);
            qDebug()<<posicao<<": lmq "<<nome_reg(vm, inst->registrador)<<", "<<nome_reg(vm, inst->operando1)<<", "<<nome_reg(vm, inst->operando2);
        }
        break;
        case LIG_MENOR_QUE:
        {
            ILigMenorQ *inst = dynamic_cast<ILigMenorQ*>(instrucao);
            qDebug()<<posicao<<": lmeq "<<nome_reg(vm, inst->registrador)<<", "<<nome_reg(vm, inst->operando1)<<", "<<nome_reg(vm, inst->operando2);
        }
        break;
        case LIG_MENOR_QUE_IM:
        {
            ILigMenorQIm *inst = dynamic_cast<ILigMenorQIm*>(instrucao);
            qDebug()<<posicao<<": lmeq "<<nome_reg(vm, inst->registrador)<<", "<<nome_reg(vm, inst->operando1)<<", "<<nome_reg(vm, inst->operando2);
        }
        break;
        case LIG_MAIOR_EQ:
        {
            ILigMaiorEq *inst = dynamic_cast<ILigMaiorEq*>(instrucao);
            qDebug()<<posicao<<": lme "<<nome_reg(vm, inst->registrador)<<", "<<nome_reg(vm, inst->operando1)<<", "<<nome_reg(vm, inst->operando2);
        }
        break;
        case LIG_MAIOR_EQ_IM:
        {
            ILigMaiorEqIm *inst = dynamic_cast<ILigMaiorEqIm*>(instrucao);
            qDebug()<<posicao<<": lme "<<nome_reg(vm, inst->registrador)<<", "<<nome_reg(vm, inst->operando1)<<", "<<nome_reg(vm, inst->operando2);
        }
        break;
        case LIG_MENOR_EQ:
        {
            ILigMenorEq *inst = dynamic_cast<ILigMenorEq*>(instrucao);
            qDebug()<<posicao<<": lmee "<<nome_reg(vm, inst->registrador)<<", "<<nome_reg(vm, inst->operando1)<<", "<<nome_reg(vm, inst->operando2);
        }
        break;
        case LIG_MENOR_EQ_IM:
        {
            ILigMenorEqIm *inst = dynamic_cast<ILigMenorEqIm*>(instrucao);
            qDebug()<<posicao<<": lmee "<<nome_reg(vm, inst->registrador)<<", "<<nome_reg(vm, inst->operando1)<<", "<<nome_reg(vm, inst->operando2);
        }
        break;
        case LIG_EQ:
        {
            ILigEq *inst = dynamic_cast<ILigEq*>(instrucao);
            qDebug()<<posicao<<": leq "<<nome_reg(vm, inst->registrador)<<", "<<nome_reg(vm, inst->operando1)<<", "<<nome_reg(vm, inst->operando2);
        }
        break;
        case LIG_EQ_IM:
        {
            ILigEqIm *inst = dynamic_cast<ILigEqIm*>(instrucao);
            qDebug()<<posicao<<": leq "<<nome_reg(vm, inst->registrador)<<", "<<nome_reg(vm, inst->operando1)<<", "<<nome_reg(vm, inst->operando2);
        }
        break;
        case LIG_NAO_EQ:
        {
            ILigNaoEq *inst = dynamic_cast<ILigNaoEq*>(instrucao);
            qDebug()<<posicao<<": lne "<<nome_reg(vm, inst->registrador)<<", "<<nome_reg(vm, inst->operando1)<<", "<<nome_reg(vm, inst->operando2);
        }
        break;
        case LIG_NAO_EQ_IM:
        {
            ILigNaoEqIm *inst = dynamic_cast<ILigNaoEqIm*>(instrucao);
            qDebug()<<posicao<<": lne "<<nome_reg(vm, inst->registrador)<<", "<<nome_reg(vm, inst->operando1)<<", "<<nome_reg(vm, inst->operando2);
        }
        break;
        case NAO_BIT:
        {
            INaoBit *inst = dynamic_cast<INaoBit*>(instrucao);
            qDebug()<<posicao<<": nao "<<nome_reg(vm, inst->registrador)<<", "<<nome_reg(vm, inst->operando1);
        }
        break;
        case NAO_BIT_IM:
        {
            INaoBitIm *inst = dynamic_cast<INaoBitIm*>(instrucao);
            qDebug()<<posicao<<": nao "<<nome_reg(vm, inst->registrador)<<", "<<nome_reg(vm, inst->operando1);
        }
        break;
        case NADA:
        {
            ICmp *inst = dynamic_cast<ICmp*>(instrucao);
            qDebug()<<posicao<<": nada";
        }
        break;
        case ESCRITA_PALAVRA:
        {
            IEscritaPalavraIm *inst = dynamic_cast<IEscritaPalavraIm*>(instrucao);
            if(inst->palavra->compare("\n")==0||inst->palavra->compare("\r\n")==0)
                qDebug()<<posicao<<": ecos \\n";
            else
                qDebug()<<posicao<<": ecos "<<*inst->palavra;
        }
        break;
        case ESCRITA_CHAR:
        {
            IEscritaChar *inst = dynamic_cast<IEscritaChar*>(instrucao);
            qDebug()<<posicao<<": ecoc "<<nome_reg(vm, inst->m);
        }
        break;
        case ESCRITA_CHAR_IM:
        {
            IEscritaCharIm *inst = dynamic_cast<IEscritaCharIm*>(instrucao);
            qDebug()<<posicao<<": ecoc "<<inst->m;
        }
        break;
        case ESCRITA_INT:
        {
            IEscritaInt *inst = dynamic_cast<IEscritaInt*>(instrucao);
            qDebug()<<posicao<<": eco "<<nome_reg(vm, inst->m);
        }
        break;
        case ESCRITA_INT_IM:
        {
            IEscritaIntIm *inst = dynamic_cast<IEscritaIntIm*>(instrucao);
            qDebug()<<posicao<<": eco "<<inst->m;
        }
        break;
        case ESCRITA_DOUBLE:
        {
            IEscritaDouble *inst = dynamic_cast<IEscritaDouble*>(instrucao);
            qDebug()<<posicao<<": ecor "<<nome_reg(vm, inst->m);
        }
        break;
        case ESCRITA_DOUBLE_IM:
        {
            IEscritaDoubleIm *inst = dynamic_cast<IEscritaDoubleIm*>(instrucao);
            qDebug()<<posicao<<": ecor "<<inst->m;
        }
        break;
        case RET:
        {
            IRet *inst = dynamic_cast<IRet*>(instrucao);
            qDebug()<<posicao<<": ret "<<nome_reg(vm, inst->registrador);
        }
        break;
        case TROCA:
        {
            ITroca *inst = dynamic_cast<ITroca*>(instrucao);
            qDebug()<<posicao<<": trc "<<nome_reg(vm, inst->registrador1)<<", "<<nome_reg(vm, inst->registrador2);
        }
        break;
        case RESTO:
        {
            IResto *inst = dynamic_cast<IResto*>(instrucao);
            qDebug()<<posicao<<": rest "<<nome_reg(vm, inst->registrador)<<", "<<nome_reg(vm, inst->operando1)<<", "<<nome_reg(vm, inst->operando2);
        }
        break;
        case RESTO_IM:
        {
            IRestoIm *inst = dynamic_cast<IRestoIm*>(instrucao);
            qDebug()<<posicao<<": rest "<<nome_reg(vm, inst->registrador)<<", "<<nome_reg(vm, inst->operando1)<<", "<<nome_reg(vm, inst->operando2);
        }
        break;
        case NEG:
        {
            INeg *inst = dynamic_cast<INeg*>(instrucao);
            qDebug()<<posicao<<": neg "<<nome_reg(vm, inst->registrador)<<", "<<nome_reg(vm, inst->operando1);
        }
        break;
        case NEG_IM:
        {
            INegIm *inst = dynamic_cast<INegIm*>(instrucao);
            qDebug()<<posicao<<": neg "<<nome_reg(vm, inst->registrador)<<", "<<nome_reg(vm, inst->operando1);
        }
        break;
        case BOOLEAN:
        {
            IBoolean *inst = dynamic_cast<IBoolean*>(instrucao);
            qDebug()<<posicao<<": bool "<<nome_reg(vm, inst->registrador);
        }
        break;
        case POTENCIA:
        {
            IPotencia *inst = dynamic_cast<IPotencia*>(instrucao);
            qDebug()<<posicao<<": pot "<<nome_reg(vm, inst->registrador)<<", "<<nome_reg(vm, inst->operando1)<<", "<<nome_reg(vm, inst->operando2);
        }
        break;
        case POTENCIA_IM:
        {
            IPotenciaIm *inst = dynamic_cast<IPotenciaIm*>(instrucao);
            qDebug()<<posicao<<": pot "<<nome_reg(vm, inst->registrador)<<", "<<nome_reg(vm, inst->operando1)<<", "<<nome_reg(vm, inst->operando2);
        }
        break;
        case SISTEMA:
        {
            ISistema *inst = dynamic_cast<ISistema*>(instrucao);
            qDebug()<<posicao<<": sis "<<nome_comando(inst->comando);
        }
        break;
        case DEBUG_PASSO:
        {
            IDebugPasso *inst = dynamic_cast<IDebugPasso*>(instrucao);
            qDebug()<<posicao<<": debug_passo linha: "<<inst->linha;
        }
        break;
        case DEBUG_EMPILHA:
        {
            IDebugEmpilhaExec *inst = dynamic_cast<IDebugEmpilhaExec*>(instrucao);
            qDebug()<<posicao<<": debug_empilha_exec";
        }
        break;
        case DEBUG_DESEMPILHA:
        {
            IDebugDesempilhaExec *inst = dynamic_cast<IDebugDesempilhaExec*>(instrucao);
            qDebug()<<posicao<<": debug_desempilha_exec";
        }
        break;
    }
}

QString nome_reg(MaquinaVirtual &vm, CelulaMemoria &celula)
{
    if(&vm.eax == &celula)
        return "eax";
    if(&vm.ebx == &celula)
        return "ebx";
    if(&vm.ecx == &celula)
        return "ecx";
    if(&vm.edx == &celula)
        return "edx";
    if(&vm.pp == &celula)
        return "pp";
    if(&vm.bp == &celula)
        return "bp";
    if(&vm.er == &celula)
        return "er";
    if(&vm.pg == &celula)
        return "pg";

    char temp[30];
    sprintf(temp, "%d", celula.toInt());

    return temp;
}

QString nome_tipo_cast(TipoVariavel::TipoVariavel tipo)
{
    if(tipo == TipoVariavel::TIPO_INT)
        return "INT";
    if(tipo == TipoVariavel::TIPO_CAR)
        return "CAR";

    return "REAL";
}

QString nome_comando(Sistema::Comando comando)
{
    switch(comando)
    {
        case Sistema::LIMPAR:
        {
            return "limpar";
        }
        break;
        case Sistema::NOVA_LINHA:
        {
            return "nova linha";
        }
        break;
    }
}
