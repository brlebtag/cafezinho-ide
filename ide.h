#ifndef IDE_H
#define IDE_H

#include <QMainWindow>
#include <QString>
#include <QHash>
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
    QHash<QString, int> fileOpened;
    QList<Document*> arquivos;
    QString lastPath;

private slots:
    void actionAbrirClicked(bool checked = false);
    void actionNovoClicked(bool checked = false);
    void actionFecharClicked(bool checked = false);
    void actionSairClicked(bool checked = false);
    void actionSalvarClicked(bool checked = false);
    void actionSalvarComoClicked(bool checked = false);
    void plainTextEditTextChanged();
};

#endif // IDE_H
