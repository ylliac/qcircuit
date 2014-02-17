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
#include <iostream>

FBPComponent::FBPComponent()
: selfStarting(false)
{
    qRegisterMetaType<QVariant > ("QVariant");
    setTerminationEnabled(true);
}

FBPComponent::~FBPComponent()
{
    //------------------------------------------------------------------
    // STOP THREAD 
    //------------------------------------------------------------------
    if(!isFinished())
    {
        terminate();
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
    FBPInputPort* port = new FBPInputPort(name);
    inputPorts.insert(port->getName(), port);

    Q_ASSERT(QObject::connect(port, SIGNAL(received(QVariant)), this, SLOT(activate())));

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
    //TODO ACY
    std::cout << "[LOG] " << "Activate component " << metaObject()->className() << std::endl;
    
    if (isFinished())
    {
        return;
    }

    if (!isRunning())
    {
        start(QThread::NormalPriority);
    }
}

void FBPComponent::run()
{
    //TODO ACY
    std::cout << "[LOG] " << "Execute component " << metaObject()->className() << std::endl;
    
    execute();
    
    //TODO ACY
    std::cout << "[LOG] " << "Terminate component " << metaObject()->className() << std::endl;
}

QVariant FBPComponent::receive(QString name)
{
    return getInputPort(name)->pop();
}

int FBPComponent::received(QString name)
{
    return getInputPort(name)->size();
}

void FBPComponent::send(QString name, QVariant value)
{
    getOutputPort(name)->send(value);
}

bool FBPComponent::isSelfStarting()
{
    return selfStarting;
}

void FBPComponent::setSelfStarting(bool value)
{
    selfStarting = value;
}

