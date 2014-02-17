/* 
 * File:   FBPOutputPort.cpp
 * Author: acailly
 * 
 * Created on 14 février 2014, 18:19
 */

#include "FBPOutputPort.h"

FBPOutputPort::FBPOutputPort(QString name) 
: FBPPort(name) 
{
}

FBPOutputPort::~FBPOutputPort()
{
}

void FBPOutputPort::send(QVariant value)
{
    emit sent(value);
}

