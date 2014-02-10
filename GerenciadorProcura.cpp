#include "GerenciadorProcura.h"

GerenciadorProcura::GerenciadorProcura(QObject *parent) :
    QObject(parent)
{
    visivel = false;
}

bool GerenciadorProcura::isVisivel()
{
    return this->visivel;
}

void GerenciadorProcura::setVisivel(bool visivel)
{
    this->visivel = visivel;
}

QWidget *GerenciadorProcura::getWidget()
{
    return this->widget;
}

QPushButton *GerenciadorProcura::getBotaoFechar()
{
    return this->botaoFechar;
}

void GerenciadorProcura::atualizarEditor()
{

}

void GerenciadorProcura::mudouEditor(QPlainTextEdit *edit)
{
    this->edit = edit;
    qDebug()<<edit;
}
