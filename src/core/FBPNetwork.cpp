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

#include "FBPInputPort.h"
#include "FBPOutputPort.h"

FBPNetwork::FBPNetwork(QObject* parent)
: FBPComponent(parent), isDefined(false)
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
    // Define the network
    //------------------------------------------------------------------
    if(!isDefined)
    {
        define();
        isDefined = true;
    }
    
    // Initiate self starters components
    //------------------------------------------------------------------
    initiate();

    // Wait until no component is active
    //------------------------------------------------------------------
    QMutexLocker locker(&mutex);
    monitor.wait(&mutex);
    
    // Cleanup
    //------------------------------------------------------------------
    foreach(FBPComponent* component, componentMap.values())
    {
        component->removeListener(this);
    }
    componentMap.clear();
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
    
    component->addListener(this);
}

bool FBPNetwork::initialize(QVariant value, FBPComponent* target, QString inPortName)
{
    FBPInputPort* input = target->getInputPort(inPortName);
    if(input == NULL){
        return false;
    }
    
    input->initialize(value);
    target->setSelfStarting(true);
    
    return true;
}

bool FBPNetwork::initialize(QVariant value, QString target, QString inPortName)
{
    FBPComponent* targetComponent = getComponent(target);
    if(targetComponent == NULL){
        return false;
    }
    
    return initialize(value, targetComponent, inPortName);
}

bool FBPNetwork::initialize(QVariant value, QString target)
{
    QStringList outputList = target.split(".");
    if (outputList.size() != 2)
    {
        return false;
    }

    QString toComponent = outputList.at(0);
    QString toPort = outputList.at(1);
    
    return initialize(value, toComponent, toPort);
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
    
    output->connect(input);
    return true;
}

//TODO ACY A implémenter 
//bool FBPNetwork::connectSubIn(QString inPortName, FBPComponent* target, QString targetPortName)
//{
//    FBPInputPort* subInput = getInputPort(inPortName);
//    if(subInput == NULL){
//        return false;
//    }
//    
//    FBPInputPort* componentInput = target->getInputPort(targetPortName);
//    if(componentInput == NULL){
//        return false;
//    }
//    
//    return QObject::connect(subInput, SIGNAL(received(QVariant)), componentInput, SLOT(onReceive(QVariant)), Qt::DirectConnection);
//}
//    
//bool FBPNetwork::connectSubOut(FBPComponent* source, QString sourcePortName, QString outPortName)
//{    
//    FBPOutputPort* componentOutput = source->getOutputPort(sourcePortName);
//    if(componentOutput == NULL){
//        return false;
//    }
//    
//    FBPOutputPort* subOutput = getOutputPort(outPortName);
//    if(subOutput == NULL){
//        return false;
//    }
//    
//    return QObject::connect(componentOutput, SIGNAL(sent(QVariant)), subOutput, SLOT(send(QVariant)), Qt::DirectConnection);
//}
//
//bool FBPNetwork::connectSubInToOut(QString inPortName, QString outPortName)
//{
//    FBPInputPort* subInput = getInputPort(inPortName);
//    if(subInput == NULL){
//        return false;
//    }
//    
//    FBPOutputPort* subOutput = getOutputPort(outPortName);
//    if(subOutput == NULL){
//        return false;
//    }
// 
//    return QObject::connect(subInput, SIGNAL(received(QVariant)), subOutput, SLOT(send(QVariant)), Qt::DirectConnection);
//}

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

void FBPNetwork::componentActivated(FBPComponent* component)
{
    activeComponentCounter->increase();
}

void FBPNetwork::componentFinished(FBPComponent* component)
{
    bool empty = activeComponentCounter->decrease();
    if(empty)
    {
        QMutexLocker locker(&mutex);
        monitor.wakeAll();
    }
}

