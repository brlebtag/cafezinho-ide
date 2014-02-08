#ifndef IRPARA_H
#define IRPARA_H

#include <QDialog>
#include <QIntValidator>

namespace Ui {
class IrPara;
}

class IrPara : public QDialog
{
    Q_OBJECT

public:
    explicit IrPara(QWidget *parent = 0);
    ~IrPara();
    int getNumeroLinha();
private:
    Ui::IrPara *ui;
};

#endif // IRPARA_H
