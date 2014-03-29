#ifndef COMPINFO_H
#define COMPINFO_H

#include <QObject>
#include <QPlainTextEdit>

class CompThread;

class CompInfo : public QObject
{
    Q_OBJECT
public:
    static CompInfo* inst();
    QString arquivo;
    static CompThread& out();
    static void setOut(CompThread *thread);
private:
    explicit CompInfo(QObject *parent = 0);
    static CompInfo* cmpInfo;
    CompThread * thread;

public slots:

};

#endif // COMPINFO_H
