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

    //From http://www.qtcentre.org/threads/10425-QtScript-newFunction-won-t-work
        
    QScriptValue that = scriptEngine.newQObject(this, QScriptEngine::QtOwnership, QScriptEngine::ExcludeChildObjects
		| QScriptEngine::ExcludeSuperClassMethods | QScriptEngine::ExcludeSuperClassProperties);
    scriptEngine.globalObject().setProperty("self",that);
    scriptEngine.evaluate("function receive(str){return self.receiveValue(str);};");
    scriptEngine.evaluate("function send(str, val){return self.sendValue(str, val);};");

    addInputPort("SCRIPT");

    //TODO ACY Gérer des ports d'entrée et sortie variable
    addInputPort("IN");
    addOutputPort("OUT");
}

Script::~Script()
{
}

void Script::execute()
{           
    //------------------------------------------------------------------
    // READ SCRIPT FILE 
    //------------------------------------------------------------------
    QVariant scriptPacket;
    receive("SCRIPT", scriptPacket);
    
    //------------------------------------------------------------------
    // EXECUTE THE SCRIPT 
    //------------------------------------------------------------------
    scriptEngine.evaluate(scriptPacket.toString());
}

QVariant Script::receiveValue(QString name)
{    
    QVariant result;
    receive(name, result);
    return result;
}
    
void Script::sendValue(QString name, QVariant value)
{    
    send(name, value);
}
