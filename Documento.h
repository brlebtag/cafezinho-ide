#ifndef DOCUMENT_H
#define DOCUMENT_H

#include <QString>
#include <QPlainTextEdit>
#include <QCryptographicHash>
#include "EditorCodigo.h"
#include <QWidget>
#include <QApplication>
#include <QClipboard>

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
    bool isTextoSelecionado();
    bool isColarDisponivel();
private:
    bool sujo;
    QWidget *widget;
    EditorCodigo *edit;
    QString documentoId;
    QString caminhoCompleto;
    bool aberto;
};

#endif // DOCUMENT_H
