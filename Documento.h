#ifndef DOCUMENT_H
#define DOCUMENT_H

#include <QString>
#include <QPlainTextEdit>
#include <QCryptographicHash>
#include "EditorCodigo.h"
#include <QWidget>
#include <QApplication>
#include <QClipboard>
#include <QFont>
#include <QTextOption>
#include <QTextBlock>
#include <QTextDocument>
#include <QTextCursor>


class Documento
{
public:
    Documento(QWidget *widget, EditorCodigo *edit, bool sujo = false );
    bool isVazio();
    bool isSujo();
    bool isAberto();
    void sujou();
    void limpou();
    void abriu();
    void fechou();
    QString getTextoDocumento();
    void setNomeDocumento(QString fileName);
    void setTextoDocumento(QString &text);
    void setTextoDocumento(QByteArray text);
    void anexarTextoDocumento(QString &text);
    QWidget *getWidget();
    QString getDocumentoId();
    QString getCaminhoCompleto();
    void setFocus();
    void repintarEditor();
    void copiar();
    void colar();
    void recortar();
    void desfazer();
    void refazer();
    bool isTextoSelecionado();
    bool isColarDisponivel();
    bool isDesfazerDisponivel();
    bool isRefazerDisponivel();
    void setFonte(QString familia, int tamanho);
    int getQuantidadeLinhas();
    void setPosicaoCursor(int posicao); //posicao é referente a linha
    int getPosicaoCursor(); //posicao é referente a linha que o cursor se situa neste momento
    void duplicarLinha();

private:
    EditorCodigo *edit;
    bool sujo;
    QWidget *widget;
    QString documentoId;
    QString caminhoCompleto;
    bool aberto;
};

#endif // DOCUMENT_H
