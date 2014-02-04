#ifndef IDE_H
#define IDE_H

#include <QMainWindow>
#include <QString>
#include <QSet>
#include <QList>
#include <QWidget>
#include <QPlainTextEdit>
#include <QSizePolicy>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QCryptographicHash>
#include <QDebug>
#include "Documento.h"
#include "EditorCodigo.h"
#include "GerenciadorDocumento.h"

class GerenciadorDocumento;

namespace Ui {
class IDE;
}

class IDE : public QMainWindow
{
    Q_OBJECT

public:
    explicit IDE(QWidget *parent = 0);
    ~IDE();

private:
    Ui::IDE *ui;
    QSet<QString> docAbertos;
    GerenciadorDocumento genDoc;
    QString ultimoCaminho;
    QWidget* criarAba(QString title, int *index = 0);
    EditorCodigo* criarEditor(QWidget* aba);
    Documento* criarDocumento(QString title, int *index = 0);
    Documento* criarDocumento(QWidget* aba, EditorCodigo* edit);
    QString nomeDocParaDocId(QString &fileName);
    QString mostrarAbrirArquivo();
    QString mostrarAbrirArquivo(QString &path);
    QString mostrarSalvarArquivo();
    QString mostrarSalvarArquivo(QString path);
    int mostrarSalvarAlteracao();
    void setTextoDocumento(Documento* document, QFile *file);
    QFile *abrirArquivoLeitura(QString &fileName);
    QFile *abrirArquivoGravacao(QString &fileName);
    void reabrirAba(QString &fileName);
    void fecharFile(QFile* file);
    QString getNomeDocumento(QString &fileName);
    void setTituloAba(int index, QString title);
    void setAbaAtual(QWidget* widget);
    void setAbaAtual(int index);
    int getAbaAtual();
    QWidget* getAbaAtualWidget();
    void setDicaAba(int index, QString &tip);
    void removeAba(int index, Documento* document);
    bool gravarDocumento(Documento *document, QString &fileName);
    bool lerDocument(Documento *document, QString &fileName);
    void configurarDocumento(Documento* document, QString &fileName, int index);
    void salvarDocumento(Documento* document, QString &fileName,int index, bool salvar_como);

private slots:
    void acaoAbrir(bool checked = false);
    void acaoNovo(bool checked = false);
    void acaoFechar(bool checked = false);
    void acaoSair(bool checked = false);
    void acaoSalvar(bool checked = false);
    void acaoSalvarComo(bool checked = false);
    void alterarEditorCodigo();
    void acaoHabilitarNumeroLinha(bool checked);
    void breakpoint(int line, bool checked);
    void mudouAbaAtual(int index);
};

#endif // IDE_H
