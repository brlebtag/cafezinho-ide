#ifndef IDE_H
#define IDE_H

#include <QMainWindow>
#include <QString>
#include <QHash>
#include <QWidget>
#include <QPlainTextEdit>
#include <QSizePolicy>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>

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
    QHash<QFile,int> *fileOpened;
private slots:
    void actionAbrirClicked(bool checked = false);
    int num_arquivos_aberto;
    int num_arquivos_nao_salvo;
private:
    QHash<int, QPlainTextEdit*> arquivos;
private slots:
    void actionNovoClicked(bool checked = false);
    void actionFecharClicked(bool checked = false);
    void actionSairClicked(bool checked = false);
};

#endif // IDE_H
