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
    QSet<QString> fileOpened;
    GerenciadorDocumento docMan;
    QList<Documento*> arquivos;
    QString lastPath;
    Documento* criarAba(QString title, int *index = 0);
    QString fileNameToFileId(QString &fileName);
    QString showAbrirArquivo();
    QString showAbrirArquivo(QString &path);
    QString showSalvarArquivo();
    QString showSalvarArquivo(QString path);
    int showSalvarAlteracao();
    void setDocumentText(Documento* document, QFile *file);
    QFile *abrirArquivoLeitura(QString &fileName);
    QFile *abrirArquivoGravacao(QString &fileName);
    void reabrirAba(QString &fileName);
    void fecharFile(QFile* file);
    QString getRealFileName(QString &fileName);
    void setAbaTitle(int index, QString title);
    void setCurrentAba(QWidget* widget);
    void setCurrentAba(int index);
    int getCurrentAba();
    void setTabToolTip(int index, QString &tip);
    void removeAba(int index, Documento* document);
    bool writeDocument(Documento *document, QString &fileName);
    bool readDocument(Documento *document, QString &fileName);
    void configurarDocumento(Documento* document, QString &fileName, int index);
    void salvarDocumento(Documento* document, QString &fileName,int index, bool salvar_como);

private slots:
    void actionAbrirClicked(bool checked = false);
    void actionNovoClicked(bool checked = false);
    void actionFecharClicked(bool checked = false);
    void actionSairClicked(bool checked = false);
    void actionSalvarClicked(bool checked = false);
    void actionSalvarComoClicked(bool checked = false);
    void plainTextEditTextChanged();
    void actionNumero_da_linhaToggled(bool checked);
    void breakpoint(int line, bool checked);
};

#endif // IDE_H
