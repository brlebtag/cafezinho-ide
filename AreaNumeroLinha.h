#ifndef LINENUMBERAREA_H
#define LINENUMBERAREA_H

#include <QWidget>
#include "EditorCodigo.h"

class EditorCodigo;
class QResizeEvent;
class QSize;

class AreaNumeroLinha : public QWidget
{
    Q_OBJECT
public:
    AreaNumeroLinha(EditorCodigo *editor);
    QSize sizeHint() const;
    QSize minimumSizeHint() const;
private:
     EditorCodigo *editorCodigo;
protected:
     void paintEvent(QPaintEvent *event);
     void mousePressEvent (QMouseEvent * event);

signals:
    void clicouAreaNumero(int line);

public slots:

};

#endif // LINENUMBERAREA_H
