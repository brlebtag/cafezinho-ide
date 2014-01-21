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
private:
     CodeEditor *codeEditor;
protected:
     void paintEvent(QPaintEvent *event);
signals:

public slots:

};

#endif // LINENUMBERAREA_H
