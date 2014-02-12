#ifndef DOCUMENTO_H
#define DOCUMENTO_H

#include <QObject>
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
#include "Realcador.h"

class Documento : public QObject
{
    Q_OBJECT
public:
    explicit Documento(QWidget *widget, EditorCodigo *edit, bool sujo = false);
    bool isVazio();
    bool isSujo();
    bool isAberto();
    void sujou();
    void limpou();
    void abriu();
    void fechou();
    void instalarRealcador();
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
    QPlainTextEdit* getEditor();

private:
    bool primeiraChamada;
    EditorCodigo *edit;
    bool sujo;
    QWidget *widget;
    QString documentoId;
    QString caminhoCompleto;
    bool aberto;

signals:

public slots:

};

#endif // DOCUMENTO_H
