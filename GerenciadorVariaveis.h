#ifndef GERENCIADORVARIAVEIS_H
#define GERENCIADORVARIAVEIS_H

#include <QObject>
#include "arvore_abstrata.h"
#include "GenVar.h"
#include "GenVarEscalar.h"
#include "GenVarVetorial.h"
#include <QTreeWidget>
#include <QHash>
#include "MaquinaVirtual.h"

class GerenciadorVariaveis : public QObject
{
    Q_OBJECT
public:
    explicit GerenciadorVariaveis(QTreeWidget* widget, QObject *parent = 0);
    void adicionar(MaquinaVirtual &vm, No* no, int inicio_variavel);
    void remover(MaquinaVirtual &vm, No *no);

private:
    QHash<No*, GenVar*> variaveis;
    QTreeWidget* widget;

signals:

public slots:
    void atualizar(MaquinaVirtual &vm);

};

#endif // GERENCIADORVARIAVEIS_H
