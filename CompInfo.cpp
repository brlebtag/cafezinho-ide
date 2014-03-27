#include "CompInfo.h"

CompInfo* CompInfo::cmpInfo = NULL;

CompInfo *CompInfo::inst()
{
    if(cmpInfo==NULL)
        cmpInfo = new CompInfo();
    return cmpInfo;
}

CompInfo::CompInfo(QObject *parent) :
    QObject(parent)
{
}
