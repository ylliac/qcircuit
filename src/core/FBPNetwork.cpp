/* 
 * File:   FBPNetwork.cpp
 * Author: acailly
 * 
 * Created on 17 février 2014, 12:07
 */

#include "FBPNetwork.h"

#include <iostream>

#include <QtCore/QStringList>

FBPNetwork::FBPNetwork()
{
}

FBPNetwork::~FBPNetwork()
{
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
    
    //TODO ACY
    std::cout << "[LOG] " 
            << "Connecting " << source->metaObject()->className()
            << "." << outPortName.toStdString()
            << " --> " << target->metaObject()->className()
            << "." << inPortName.toStdString()
            << std::endl;
    
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

    // Wait until every component is finished
    //------------------------------------------------------------------
    waitForAll();    
}

void FBPNetwork::initiate()
{
    QList<FBPComponent*> components = componentMap.values();
    foreach(FBPComponent* component, components)
    {
        if(component->isSelfStarting())
        {
            //TODO ACY
//            std::cout << "[LOG] " << "Autostarting component " << component->metaObject()->className() << std::endl;

            component->activate();
        }
    }
}

void FBPNetwork::waitForAll()
{
    bool retest = true;
    while(retest){
        retest = false;
        
        QList<FBPComponent*> components = componentMap.values();
        foreach(FBPComponent* component, components)
        {        
            //TODO ACY
//            std::cout << "[LOG] " << "Waiting for component " << component->metaObject()->className() << std::endl;

            retest |= component->isRunning();
            component->wait();
        }
    }
    
    //TODO ACY
//    std::cout << "[LOG] " << "Everything is finished" << std::endl;
}

