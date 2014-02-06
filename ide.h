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
#include <QPoint>
#include "GerenciadorMenuFonte.h"
#include "fontedialog.h"

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
    //GerenciadorMenuFonte genFonte;
    QString ultimoCaminho;
    QSettings configuracoes;
    bool ver_funcoes;
    bool ver_debugger;
    bool ver_exec_prog;

    int tamanho_fonte;
    QString familia_fonte;

    //Metodos

    //Gerenciar Criacao de Documento
    QWidget* criarAba(QString title, int *index = 0);
    QPushButton* criarBotaoFecharAba(QWidget *pai);
    QPushButton* criarBotaoMaisAba(QWidget *pai);
    EditorCodigo* criarEditor(QWidget* aba);
    Documento* criarDocumento(QString title, int *index = 0);
    Documento* criarDocumento(QWidget* aba, EditorCodigo* edit);

    //Mensagens

    //Mensagens para Abrir
    QString mostrarAbrirArquivo();
    QString mostrarAbrirArquivo(QString &path);

    //Mensagens para Salvar
    QString mostrarSalvarArquivo();
    QString mostrarSalvarArquivo(QString path);
    int mostrarSalvarAlteracao();

    //Mensagens de Erro
    void msgErroSalvar(QFile* file = 0);
    void msgErroAbrir(QFile* file = 0);


    //Gerenciar Manipulação de Documentos
    void setTituloAba(int index, QString title);
    void setAbaAtual(QWidget* widget);
    void setAbaAtual(int index);
    int getAbaAtual();
    QWidget* getAbaAtualWidget();
    void setTextoDocumento(Documento* document, QFile *file);
    void setDicaAba(int index, QString &tip);
    void reabrirAba(QString &fileName);


    //Gerenciar nome do documento
    QString getNomeDocumento(QString &fileName);
    QString getCaminhoDocumento(QString &fileName);
    QString nomeDocParaDocId(QString &fileName);


    //Gerenciar Leitura e gravação de   Documentos
    QFile *abrirArquivoLeitura(QString &fileName);
    QFile *abrirArquivoGravacao(QString &fileName);
    bool gravarDocumento(Documento *document, QString &fileName);
    bool lerDocument(Documento *document, QString &fileName);
    void configurarDocumento(Documento* document, QString &fileName, int index);
    void fecharFile(QFile* file);
    void salvarDocumento(Documento* document, QString &fileName,int index, bool salvar_como);
    void abrirDocumento(QString &fileName);

    //Gerenciar Remoção de abas e documentos
    void removeAba(int index, Documento* document);
    bool salvarEFecharAbas(bool fechar = true);

    //Gerenciar Configuracoes

    //Gravar Configurações
    void gravarConfiguracoes();
    void gravarConfiguracoesMenuVer();
    void gravarConfiguracoesFonte();

    //Reestabeler Configurações
    void restaurarConfiguracoes();
    void restaurarConfiguracoesMenuVer();
    void restaurarConfiguracoesFonte();

    //Gerenciar o Editor
    void configurarFonteEditor();

protected:
    void closeEvent(QCloseEvent *event);

private slots:

    // Menu Arquivo
    void acaoAbrir(); //OK
    void acaoNovo(); //OK
    void acaoFechar(); //OK
    void acaoSair(); //OK
    void acaoSalvar(); //OK
    void acaoSalvarComo(); //OK
    void menuReabrirClicou(QString caminho);
    void menuArquivoClicado();

    //EditorCodigo
    void alterarEditorCodigo(); //OK
    void breakpoint(int line, bool checked); //OK

    // Tab Widget Arquivos
    void mudouAbaAtual(int index); //OK
    void botaoFecharTabClicado();
    void botaoMaisTabClicado();

    //Menu Ver
    void acaoHabilitarFuncoes(bool checked);
    void acaoHabilitarDebug(bool checked);
    void acaoHabilitarExecProg(bool checked);
    void acaoHabilitarNumeroLinha(bool checked); //OK
    void reiniciarInterfaceClicado();

    //Menu Documento
    void proximoDocumento();
    void anteriroDocumento();
    void salvarTodosDocumentos();
    void fecharTodosDocumentos();

    //Menu Editar
    void copiarDocumento();
    void colarDocumento();
    void recortarDocumento();
    void menuEditarClicado();
    void desfazerDocumento();
    void refazerDocumento();

    //Menu Editor
    void aumentarFonte();
    void diminuirFonte();
    void reiniciarFonte();
    void fonteClicado();

    //Gerenciar Fonte
    //void mudouFonte(QString fonte);
};

#endif // IDE_H
