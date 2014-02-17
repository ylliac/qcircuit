/* 
 * File:   FBPPort.cpp
 * Author: acailly
 * 
 * Created on 17 février 2014, 09:55
 */

#include "FBPPort.h"

FBPPort::FBPPort(QString name)
: name(name)
{
}

FBPPort::~FBPPort()
{
}

QString FBPPort::getName()
{
    return name;
}

