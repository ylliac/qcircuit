/* 
 * File:   FBPComponent.cpp
 * Author: acailly
 * 
 * Created on 13 février 2014, 18:17
 */

#include "FBPComponent.h"

#include <QtCore/QRegExp>
#include <QtCore/QMetaObject>
#include <QtCore/QMetaProperty>
#include <QtCore/QtConcurrentRun>
#include <QtCore/QFutureWatcher>
#include <QtCore/QEventLoop>
#include <iostream>

#include "FBPInputPort.h"
#include "FBPOutputPort.h"
#include "FBPComponentListener.h"

FBPComponent::FBPComponent(QObject* parent)
: QObject(parent),
selfStarting(false),
state(NOT_STARTED)
{
    setObjectName(metaObject()->className());
    
    qRegisterMetaType<QVariant > ("QVariant");
}

FBPComponent::~FBPComponent()
{
    //------------------------------------------------------------------
    // STOP THREAD 
    //------------------------------------------------------------------
    if(!future.isFinished())
    {
        future.cancel();
        future.waitForFinished();
    }
        
    //------------------------------------------------------------------
    // INPUT PORTS 
    //------------------------------------------------------------------
    QList<FBPInputPort*> inputs = inputPorts.values();

    foreach(FBPInputPort* port, inputs)
    {
        delete port;
    }

    //------------------------------------------------------------------
    // OUTPUT PORTS 
    //------------------------------------------------------------------
    QList<FBPOutputPort*> outputs = outputPorts.values();

    foreach(FBPOutputPort* port, outputs)
    {
        delete port;
    }
}

FBPInputPort* FBPComponent::addInputPort(QString name)
{
    FBPInputPort* port = new FBPInputPort(name, this);
    inputPorts.insert(port->getName(), port);

    return port;
}

FBPOutputPort* FBPComponent::addOutputPort(QString name)
{
    FBPOutputPort* port = new FBPOutputPort(name);
    outputPorts.insert(port->getName(), port);

    return port;
}

FBPInputPort* FBPComponent::getInputPort(QString name)
{
    FBPInputPort* result = NULL;
    
    if(inputPorts.contains(name))
    {
        result = inputPorts.value(name);
    }
    
    return result;
}

FBPOutputPort* FBPComponent::getOutputPort(QString name)
{
    FBPOutputPort* result = NULL;
    
    if(outputPorts.contains(name))
    {
        result = outputPorts.value(name);
    }
    
    return result;
}

void FBPComponent::activate()
{        
    if (state == NOT_STARTED)
    {
        future = QtConcurrent::run(this, &FBPComponent::execute0);
    }
}

void FBPComponent::execute0()
{
    //TODO ACY 
//    std::cout << "START: " << objectName().toStdString() << std::endl;
    
    state = ACTIVATED;
    foreach(FBPComponentListener* listener, listeners)
    {
        listener->componentActivated(this);
    }
    
    execute();
    
    //At the end of execution, close the remaining output ports
    foreach(FBPOutputPort* outputPort, outputPorts.values())
    {
        outputPort->close();
    }
    
    //TODO ACY 
//    std::cout << "FINISH: " << objectName().toStdString() << std::endl;
    
    state = FINISHED;
    foreach(FBPComponentListener* listener, listeners)
    {
        listener->componentFinished(this);
    }
}

QVariant FBPComponent::receive(QString name)
{
    QVariant outData;
    getInputPort(name)->receive(outData);
    return outData;
}

bool FBPComponent::receive(QString name, QVariant& outData)
{
    return getInputPort(name)->receive(outData);
}

int FBPComponent::received(QString name)
{
    return getInputPort(name)->size();
}

void FBPComponent::send(QString name, QVariant value)
{
    getOutputPort(name)->send(value);
}

void FBPComponent::close(QString name)
{
    getOutputPort(name)->close();
}

bool FBPComponent::isSelfStarting()
{
    return selfStarting;
}

void FBPComponent::setSelfStarting(bool value)
{
    selfStarting = value;
}

void FBPComponent::wait()
{
    QFutureWatcher<void> watcher;    
    QEventLoop loop;
    connect(&watcher, SIGNAL(finished()), &loop, SLOT(quit()));
    watcher.setFuture(future);
    loop.exec();    
}

bool FBPComponent::isActive()
{
    return state == ACTIVATED;
}

bool FBPComponent::isFinished()
{
    return state == FINISHED;
}
    
void FBPComponent::addListener(FBPComponentListener* listener)
{
    listeners.insert(listener);
}
    
void FBPComponent::removeListener(FBPComponentListener* listener)
{
    listeners.remove(listener);    
}


