#ifndef IDE_H
#define IDE_H

#include <QMainWindow>
#include <QString>
#include <QFileDialog>
#include <QFile>
#include <QHash>
#include <QMessageBox>

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
    int num_arquivo_abertos;
    int num_arquivo_nao_salvo;
    QHash<QFile,int> *fileOpened;
private slots:
    void actionAbrirClicked(bool checked = false);
};

#endif // IDE_H
