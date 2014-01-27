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
#include "document.h"
#include "codeeditor.h"
#include "documentmanager.h"

namespace Ui {
class IDE;
}

class IDE : public QMainWindow
{
    Q_OBJECT

public:
    explicit IDE(QWidget *parent = 0);
    ~IDE();
    static const void* null;

private:
    Ui::IDE *ui;
    QSet<QString> fileOpened;
    DocumentManager docMan;
    QList<Document*> arquivos;
    QString lastPath;
    Document* criarAba(QString title);
    QString fileNameToFileId(QString &fileName);
    QString showAbrirArquivo();
    QString showAbrirArquivo(QString &path);
    QString showSalvarArquivo();
    QString showSalvarArquivo(QString path);
    int showSalvarAlteracao();
    void setDocumentText(Document* document, QFile *file);
    QFile* abrirArquivoLeitura(QString &fileName);
    QFile *abrirArquivoGravacao(QString &fileName);
    void reabrirAba(QString &fileName);
    void fecharFile(QFile* file);
    QString getRealFileName(QString &fileName);
    void setAbaTitle(int index, QString title);
    void setCurrentAba(QWidget* widget);
    void setCurrentAba(int index);
    int getCurrentAba();
    void setTabToolTip(int index, QString &tip);
    void removeAba(int index, Document* document);
    bool writeDocument(Document *document, QString &fileName);
    void readDocument(Document *document, int index, QString &fileName, QFile *file);

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
