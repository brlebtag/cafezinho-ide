#ifndef PROCURAR_H
#define PROCURAR_H

#include <QWidget>
#include <QString>

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
    QString getTextoLocalizar();
    QString getTextoSubstituir();

private:
    Ui::Procurar *ui;
    bool substituir;

    //metodos
    void atualizarInterface();

signals:
    void localizarClicado();
    void substituirClicado();
    void localizarAnteriorClicado();
    void substituirTudoClicado();
    void ignorarMaisculaMarcado(bool checked);
    void palavraInteiraMarcado(bool checked);
    void mudouPalavraProcurada(QString palavra);
    void mudouPalavraSubstituir(QString palavra);


public slots:
    void localizar();
    void substitui();
    void localizarAnterior();
    void substituirTudo();
    void ignorarMaiscula();
    void palavraInteira();
    void palavraProcurada();
    void palavraSubstituir();
};

#endif // PROCURAR_H
