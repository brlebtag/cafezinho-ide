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
#include "GerenciadorMenuReabrir.h"
#include "QPushButton"
#include "QIcon"

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

    //propriedades
    Ui::IDE *ui;
    QSet<QString> docAbertos;
    GerenciadorDocumento genDoc;
    GerenciadorMenuReabrir genReabrir;
    QString ultimoCaminho;
    QSettings configuracoes;
    bool ver_funcoes;
    bool ver_debugger;
    bool ver_exec_prog;

    //Metodos
    QWidget* criarAba(QString title, int *index = 0);
    QPushButton* criarBotaoFecharAba(QWidget *pai);
    QPushButton* criarBotaoMaisAba(QWidget *pai);
    EditorCodigo* criarEditor(QWidget* aba);
    Documento* criarDocumento(QString title, int *index = 0);
    Documento* criarDocumento(QWidget* aba, EditorCodigo* edit);
    QString nomeDocParaDocId(QString &fileName);
    QString mostrarAbrirArquivo();
    QString mostrarAbrirArquivo(QString &path);
    QString mostrarSalvarArquivo();
    QString mostrarSalvarArquivo(QString path);
    void msgErroSalvar(QFile* file = 0);
    void msgErroAbrir(QFile* file = 0);
    int mostrarSalvarAlteracao();
    void setTextoDocumento(Documento* document, QFile *file);
    QFile *abrirArquivoLeitura(QString &fileName);
    QFile *abrirArquivoGravacao(QString &fileName);
    void reabrirAba(QString &fileName);
    void fecharFile(QFile* file);
    QString getNomeDocumento(QString &fileName);
    QString getCaminhoDocumento(QString &fileName);
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
    void abrirDocumento(QString &fileName);
    bool salvarEFecharAbas(bool fechar = true);
    void gravarConfiguracoes();
    void restaurarConfiguracoes();

protected:
    void closeEvent(QCloseEvent *event);
private slots:
    void acaoAbrir(bool checked = false); //OK
    void acaoNovo(bool checked = false); //OK
    void acaoFechar(bool checked = false); //OK
    void acaoSair(bool checked = false); //OK
    void acaoSalvar(bool checked = false); //OK
    void acaoSalvarComo(bool checked = false); //OK
    void alterarEditorCodigo(); //OK
    void acaoHabilitarNumeroLinha(bool checked); //OK
    void breakpoint(int line, bool checked); //OK
    void mudouAbaAtual(int index); //OK
    void menuReabrirClicou(QString caminho);
    void acaoHabilitarFuncoes(bool checked);
    void acaoHabilitarDebug(bool checked);
    void acaoHabilitarExecProg(bool checked);
    void botaoFecharTabClicado();
    void botaoMaisTabClicado();
    void reiniciarInterfaceClicado(bool checked);
    void proximoDocumento(bool checked);
    void anteriroDocumento(bool checked);
    void salvarTodosDocumentos(bool checked);
    void fecharTodosDocumentos(bool checked);
    void copiarDocumento();
    void colarDocumento();
    void recortarDocumento();
    void menuEditarClicado();
};

#endif // IDE_H
