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
#include <QFontMetrics>
#include <QSet>

class Documento : public QObject
{
    Q_OBJECT
public:
    explicit Documento(QWidget *widget, EditorCodigo *edit, QObject* botao, bool sujo = false);
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
    void setPosicaoCursor(int linha); //posicao é referente a linha
    int getPosicaoCursor(); //posicao é referente a linha que o cursor se situa neste momento
    void duplicarLinha();
    QPlainTextEdit* getEditor();
    QObject *getBotao();
    void setBotao(QObject *botao);
    void setSelecoes(QList<QTextEdit::ExtraSelection> selecoes);
    void setSelecao(QTextEdit::ExtraSelection selecao);
    void appendSelecao(QTextEdit::ExtraSelection selecao);
    void limparSelecoes();
    bool ligaDeslBreakPoint(int linha);
    int getCursorLinhaAtual();
    QSet<int>& getBreakPoints();
private:
    const static int TAB_SPACE;
    bool primeiraChamada;
    EditorCodigo *edit;
    bool sujo;
    QWidget *widget;
    QObject* botao;
    QString documentoId;
    QString caminhoCompleto;
    bool aberto;

signals:
    void textoMudou(QTextDocument *documento);

public slots:
    void texto_mudou();

};

#endif // DOCUMENTO_H
