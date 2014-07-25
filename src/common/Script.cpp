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
    scriptEngine.evaluate("function receive(str){return self.receiveValue(str);};");
    scriptEngine.evaluate("function send(str, val){return self.sendValue(str, val);};");
    
    //TODO ACY SUPPR
//    QScriptValue val = scriptEngine.evaluate("receive('SCRIPT');");
//    std::cout << "VAL = " << val.toVariant().toString().toStdString() << std::endl;
    
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

QVariant Script::receiveValue(QString name)
{
    return receive(name);
}
    
void Script::sendValue(QString name, QVariant value)
{
    sendValue(name, value);
}
