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
    return inputPorts.value(name);
}

FBPOutputPort* FBPComponent::getOutputPort(QString name)
{
    return outputPorts.value(name);
}

void FBPComponent::activate()
{
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
    execute();
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

