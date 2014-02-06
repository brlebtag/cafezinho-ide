#ifndef FONTEDIALOG_H
#define FONTEDIALOG_H

#include <QDialog>
#include <QListWidgetItem>
#include <QFont>

namespace Ui {
class FonteDialog;
}

class FonteDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FonteDialog(QString *fonte, QWidget *parent = 0);
    ~FonteDialog();

private:
    Ui::FonteDialog *ui;
    QString *fonte;

private slots:
    void itemMudou(const QString & familia);
};

#endif // FONTEDIALOG_H
