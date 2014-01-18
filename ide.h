#ifndef IDE_H
#define IDE_H

#include <QMainWindow>

namespace Ui {
class IDE;
}

class IDE : public QMainWindow
{
    Q_OBJECT

public:
    explicit IDE(QWidget *parent = 0);
    ~IDE();

private:
    Ui::IDE *ui;
};

#endif // IDE_H
