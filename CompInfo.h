#ifndef COMPINFO_H
#define COMPINFO_H

#include <QObject>
#include <QPlainTextEdit>

class CompInfo : public QObject
{
    Q_OBJECT
public:
    static CompInfo* inst();
    QString arquivo;

private:
    explicit CompInfo(QObject *parent = 0);
    static CompInfo* cmpInfo;

public slots:

};

#endif // COMPINFO_H
