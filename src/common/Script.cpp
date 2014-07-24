/* 
 * File:   Script.cpp
 * Author: acailly
 * 
 * Created on 12 février 2014, 18:25
 */

#include "Script.h"
#include "Value.h"

#include <iostream>
#include <QtCore/QVariant>

Script::Script()
{
    setObjectName(metaObject()->className());


    addInputPort("SCRIPT");

    addInputPort("IN");
    addOutputPort("OUT");
}

Script::~Script()
{
}

void Script::execute()
{   
    //From http://www.qtcentre.org/threads/10425-QtScript-newFunction-won-t-work
    
    QScriptValue that = scriptEngine.newQObject(this, QScriptEngine::QtOwnership, QScriptEngine::ExcludeChildObjects
		| QScriptEngine::ExcludeSuperClassMethods | QScriptEngine::ExcludeSuperClassProperties);
    scriptEngine.globalObject().setProperty("self",that);
//    QScriptValue val = scriptEngine.evaluate("component.test();");
//    std::cout << val.toNumber() << std::endl;
    QScriptValue val = scriptEngine.evaluate("self.receiveValue();");
    std::cout << val.toString().toStdString() << std::endl;
    
    
//    QScriptValue receiveFunction = scriptEngine.newFunction(scriptReceive);
//    scriptEngine.globalObject().setProperty("receive", receiveFunction);
//    
//    QScriptValue sendFunction = scriptEngine.newFunction(scriptSend);
//    scriptEngine.globalObject().setProperty("send", sendFunction);
    
    //------------------------------------------------------------------
    // READ SCRIPT FILE 
    //------------------------------------------------------------------
    QVariant scriptPacket;
    receive("SCRIPT", scriptPacket);
    
    //TODO ACY TEST    
    std::cout << scriptPacket.toString().toStdString() << std::endl;
    
    //------------------------------------------------------------------
    // EXECUTE THE SCRIPT 
    //------------------------------------------------------------------
    scriptEngine.evaluate(scriptPacket.toString());
}

//TODO ACY SUPPR
int Script::test()
{
    return 12;
}

//QVariant Script::receiveValue(QString name)
QVariant Script::receiveValue()
{
//    return receive(name);
    return receive("SCRIPT");
}
    
void Script::sendValue(QString name, QVariant value)
{
    sendValue(name, value);
}
