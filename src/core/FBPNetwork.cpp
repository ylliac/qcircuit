/* 
 * File:   FBPNetwork.cpp
 * Author: acailly
 * 
 * Created on 17 février 2014, 12:07
 */

#include "FBPNetwork.h"

#include <iostream>

#include <QtCore/QStringList>
#include <QtCore/QEventLoop>

FBPNetwork::FBPNetwork(QObject* parent)
: FBPComponent(parent)
{
    activeComponentCounter = new Counter(this);
}

FBPNetwork::~FBPNetwork()
{    
    //Delete components
    QList<FBPComponent*> components = componentMap.values();
    foreach(FBPComponent* component, components)
    {        
        delete component;
    }
}

void FBPNetwork::execute()
{
    // Overridden by specific networks
}

void FBPNetwork::define()
{
}

FBPComponent* FBPNetwork::getComponent(QString name)
{
    FBPComponent* result = NULL;
    if(componentMap.contains(name))
    {
        result = componentMap.value(name);
    }
    
    return result;
}

void FBPNetwork::addComponent(FBPComponent* component, QString name)
{
    Q_ASSERT(!componentMap.contains(name));
    componentMap.insert(name, component);
    
    bool check = QObject::connect(component, SIGNAL(activated()), activeComponentCounter, SLOT(increase()));
    Q_ASSERT(check);
    check = QObject::connect(component, SIGNAL(finished()), activeComponentCounter, SLOT(decrease()));
    Q_ASSERT(check);
}

void FBPNetwork::initialize(QVariant value, FBPComponent* target, QString inPortName)
{
    //TODO ACY
}

void FBPNetwork::initialize(QVariant value, QString target, QString inPortName)
{
    //TODO ACY    
}

void FBPNetwork::initialize(QVariant value, QString target)
{
    //TODO ACY    
}

bool FBPNetwork::connect(FBPComponent* source, QString outPortName, FBPComponent* target, QString inPortName)
{
    FBPOutputPort* output = source->getOutputPort(outPortName);
    if(output == NULL){
        return false;
    }
    FBPInputPort* input = target->getInputPort(inPortName);
    if(input == NULL){
        return false;
    }
    
    return QObject::connect(output, SIGNAL(sent(QVariant)), input, SLOT(onReceive(QVariant)), Qt::DirectConnection);
}

bool FBPNetwork::connect(QString source, QString outPortName, QString target, QString inPortName)
{    
    FBPComponent* sourceComponent = getComponent(source);
    if(sourceComponent == NULL){
        return false;
    }
    
    FBPComponent* targetComponent = getComponent(target);
    if(targetComponent == NULL){
        return false;
    }
       
    return connect(sourceComponent, outPortName, targetComponent, inPortName);
}

bool FBPNetwork::connect(QString source, QString target)
{
    // Parse input
    //------------------------------------------------------------------
    QStringList inputList = source.split(".");
    if (inputList.size() != 2)
    {
        return false;
    }

    QString fromComponent = inputList.at(0);
    QString fromPort = inputList.at(1);

    // Parse output
    //------------------------------------------------------------------
    QStringList outputList = target.split(".");
    if (outputList.size() != 2)
    {
        return false;
    }

    QString toComponent = outputList.at(0);
    QString toPort = outputList.at(1);
    
    return connect(fromComponent, fromPort, toComponent, toPort);
}

void FBPNetwork::go()
{    
    // Define the network
    //------------------------------------------------------------------
    define();
    
    // Initiate self starters components
    //------------------------------------------------------------------
    initiate();

    // Event loop (used to enable the signal / slot mechanism)
    // Stop when no component is active
    //------------------------------------------------------------------
    QEventLoop* eventLoop = new QEventLoop(this);
    bool check = QObject::connect(activeComponentCounter, SIGNAL(zero()), eventLoop, SLOT(quit()));
    Q_ASSERT(check);
    eventLoop->exec();
}

void FBPNetwork::initiate()
{
    QList<FBPComponent*> components = componentMap.values();
    foreach(FBPComponent* component, components)
    {
        if(component->isSelfStarting())
        {
            component->activate();
        }
    }
}

