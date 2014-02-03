#ifndef DOCUMENT_H
#define DOCUMENT_H

#include <QString>
#include <QPlainTextEdit>
#include <QCryptographicHash>
#include "codeeditor.h"
#include <QWidget>

class Documento
{
public:
    Documento(QWidget *widget, CodeEditor *edit, bool sujo = false );
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
    void repaintEdit();
private:
    bool sujo;
    QWidget *widget;
    CodeEditor *edit;
    QString documentoId;
    QString caminhoCompleto;
    bool aberto;
};

#endif // DOCUMENT_H
