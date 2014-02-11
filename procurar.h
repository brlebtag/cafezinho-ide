#ifndef PROCURAR_H
#define PROCURAR_H

#include <QWidget>

namespace Ui {
class Procurar;
}

class Procurar : public QWidget
{
    Q_OBJECT

public:
    explicit Procurar(QWidget *parent = 0);
    ~Procurar();
    void setSubstituir(bool substituir);

private:
    Ui::Procurar *ui;
    bool substituir;

    //metodos
    void atualizarInterface();
};

#endif // PROCURAR_H
