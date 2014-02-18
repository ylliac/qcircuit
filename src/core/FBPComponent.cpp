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
    setObjectName(metaObject()->className());
    
    qRegisterMetaType<QVariant > ("QVariant");
    
    thread = new QThread();
    thread->setObjectName(metaObject()->className());
    moveToThread(thread);
}

FBPComponent::~FBPComponent()
{
    //------------------------------------------------------------------
    // STOP THREAD 
    //------------------------------------------------------------------
    if(!thread->isFinished())
    {
        thread->terminate();
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
//    port->moveToThread(thread);
    inputPorts.insert(port->getName(), port);

    //TODO ACY
//    bool check = QObject::connect(port, SIGNAL(received(QVariant)), this, SLOT(activate()));
    bool check = QObject::connect(port, SIGNAL(received(QVariant)), this, SLOT(activate()), Qt::DirectConnection);
    Q_ASSERT(check);

    return port;
}

FBPOutputPort* FBPComponent::addOutputPort(QString name)
{
    FBPOutputPort* port = new FBPOutputPort(name);
//    port->moveToThread(thread);
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
//    std::cout << "[LOG] " << "Activate component " << metaObject()->className() << std::endl;
        
    //TODO ACY Pourquoi ne le lancer qu'une seule fois
//    if (isFinished())
//    {
//        return;
//    }

    if (!thread->isRunning())
    {
        thread->start(QThread::NormalPriority);
        bool check = QMetaObject::invokeMethod(this, "execute");
        Q_ASSERT(check);
    }
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

bool FBPComponent::wait()
{
    return thread->wait();
}

bool FBPComponent::isRunning()
{
    return thread->isRunning();
}


