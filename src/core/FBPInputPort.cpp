/* 
 * File:   FBPInputPort.cpp
 * Author: acailly
 * 
 * Created on 14 février 2014, 17:49
 */

#include "FBPInputPort.h"

#include "FBPComponent.h"

FBPInputPort::FBPInputPort(QString name, FBPComponent* parent) 
: FBPPort(name), parent(parent), senderCount(0)
{
}

FBPInputPort::~FBPInputPort()
{
}

void FBPInputPort::initialize(QVariant value)
{
    receivedQueue.clear();    
    receivedQueue.enqueue(value);     
}

bool FBPInputPort::receive(QVariant& outData)
{    
    bool result = false;
    
    if(!isEmpty() || !isClosed())
    {
        result = receivedQueue.dequeue(outData);        
    }
    
    return result;
}

int FBPInputPort::size() const
{
    return receivedQueue.size();
}

void FBPInputPort::send(QVariant value)
{    
    receivedQueue.enqueue(value);    
    parent->activate();
}

bool FBPInputPort::isDrained()
{
    return isEmpty() && isClosed();
}
    
bool FBPInputPort::isEmpty()
{
    return receivedQueue.empty();
}
 
bool FBPInputPort::isClosed()
{
    return senderCount == 0;
}
    
void FBPInputPort::increaseSenderCount()
{
    senderCount++;
}

void FBPInputPort::decreaseSenderCount()
{
    senderCount--;
    
    if(isDrained())
    {
        receivedQueue.close();
    }
}

