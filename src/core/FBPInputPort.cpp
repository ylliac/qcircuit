/* 
 * File:   FBPInputPort.cpp
 * Author: acailly
 * 
 * Created on 14 février 2014, 17:49
 */

#include "FBPInputPort.h"

FBPInputPort::FBPInputPort(QString name) 
: FBPPort(name), iip(false)
{
}

FBPInputPort::~FBPInputPort()
{
}

void FBPInputPort::initialize(QVariant value)
{
    iip = true;
    receivedQueue.clear();    
    receivedQueue.enqueue(value);
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
    //Input port with IIP can't be connected to another component
    Q_ASSERT(!iip);
    
    receivedQueue.enqueue(value);
    
    emit received(value);
}

