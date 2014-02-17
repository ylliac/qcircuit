/* 
 * File:   FBPInputPort.cpp
 * Author: acailly
 * 
 * Created on 14 février 2014, 17:49
 */

#include "FBPInputPort.h"

FBPInputPort::FBPInputPort(QString name) 
: FBPPort(name)
{
}

FBPInputPort::~FBPInputPort()
{
}

QVariant FBPInputPort::pop()
{    
    QVariant value;
    bool check = receivedQueue.dequeue(value);
    if(check)
    {
        return value;
    }
    else
    {
        return QVariant();
    }    
}

int FBPInputPort::size() const
{
    return receivedQueue.size();
}

void FBPInputPort::onReceive(QVariant value)
{
    receivedQueue.enqueue(value);
    
    emit received(value);
}

