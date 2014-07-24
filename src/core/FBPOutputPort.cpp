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

void FBPOutputPort::connect(FBPInputPort* receiver)
{
    receiver->increaseSenderCount();
    receivers.insert(receiver);
}

void FBPOutputPort::disconnect(FBPInputPort* receiver)
{
    receiver->decreaseSenderCount();
    receivers.remove(receiver);
}

void FBPOutputPort::send(QVariant value)
{
    foreach(FBPInputPort* receiver, receivers)
    {
        receiver->send(value);
    }
}

void FBPOutputPort::close()
{
    foreach(FBPInputPort* receiver, receivers)
    {
        disconnect(receiver);
    }
    receivers.clear();
}

