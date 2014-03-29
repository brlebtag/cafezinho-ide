#include "CompInfo.h"
#include "CompThread.h"

CompInfo* CompInfo::cmpInfo = NULL;

CompInfo *CompInfo::inst()
{
    if(cmpInfo==NULL)
        cmpInfo = new CompInfo();
    return cmpInfo;
}

CompThread &CompInfo::out()
{
    return (*CompInfo::inst()->thread);
}

void CompInfo::setOut(CompThread* thread)
{
    CompInfo::inst()->thread = thread;
}

CompInfo::CompInfo(QObject *parent) :
    QObject(parent)
{
}
