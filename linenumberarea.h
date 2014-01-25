#ifndef LINENUMBERAREA_H
#define LINENUMBERAREA_H

#include <QWidget>
#include "codeeditor.h"

class CodeEditor;
class QResizeEvent;
class QSize;

class LineNumberArea : public QWidget
{
    Q_OBJECT
public:
    LineNumberArea(CodeEditor *editor);
    QSize sizeHint() const;
    QSize minimumSizeHint() const;
private:
     CodeEditor *codeEditor;
protected:
     void paintEvent(QPaintEvent *event);
     void mousePressEvent (QMouseEvent * event);

signals:
    void lineNumberClicked(int line);

public slots:

};

#endif // LINENUMBERAREA_H
