#ifndef LINENUMBERAREA_H
#define LINENUMBERAREA_H

#include <QWidget>
#include "EditorCodigo.h"

class EditorCodigo;
class QResizeEvent;
class QSize;

class AreaNumero : public QWidget
{
    Q_OBJECT
public:
    AreaNumero(EditorCodigo *editor);
    QSize sizeHint() const;
    QSize minimumSizeHint() const;
private:
     EditorCodigo *codeEditor;
protected:
     void paintEvent(QPaintEvent *event);
     void mousePressEvent (QMouseEvent * event);

signals:
    void clicouAreaNumero(int line);

public slots:

};

#endif // LINENUMBERAREA_H
