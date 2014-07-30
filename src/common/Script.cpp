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

Script::Script(QString script)
{
    setObjectName(metaObject()->className());

    //From http://www.qtcentre.org/threads/10425-QtScript-newFunction-won-t-work
        
    QScriptValue that = scriptEngine.newQObject(this, QScriptEngine::QtOwnership, QScriptEngine::ExcludeChildObjects
		| QScriptEngine::ExcludeSuperClassMethods | QScriptEngine::ExcludeSuperClassProperties);
    scriptEngine.globalObject().setProperty("self",that);
    scriptEngine.evaluate("function echo(str){self.scriptEcho(str);};");
    scriptEngine.evaluate("function addInputPort(str){self.scriptAddInputPort(str);};");
    scriptEngine.evaluate("function addOutputPort(str){self.scriptAddOutputPort(str);};");
    scriptEngine.evaluate("function setSelfStarting(str){self.scriptSetSelfStarting(str);};");
    scriptEngine.evaluate("function receive(str){return self.scriptReceive(str);};");
    scriptEngine.evaluate("function send(str, val){self.scriptSend(str, val);};");
    
    //------------------------------------------------------------------
    // EVALUATE THE SCRIPT 
    //------------------------------------------------------------------
    QScriptSyntaxCheckResult check = scriptEngine.checkSyntax(script);
    if(check.state() != QScriptSyntaxCheckResult::Valid)
    {
        std::cerr << QString("Error in script line %1, column %2: %3")
                .arg(check.errorLineNumber())
                .arg(check.errorColumnNumber())
                .arg(check.errorMessage())
                .toStdString() << std::endl;
    }
    else if(!scriptEngine.canEvaluate(script))
    {
        std::cerr << QString("Can't evaluate script: unknown error.")
                .toStdString() << std::endl;
    }
    else
    {        
        scriptEngine.evaluate(script);
        scriptEngine.evaluate("init()");
    }
}

Script::~Script()
{
}

void Script::execute()
{           
    //------------------------------------------------------------------
    // EXECUTE THE SCRIPT 
    //------------------------------------------------------------------
    scriptEngine.evaluate("execute();");
}

QVariant Script::scriptReceive(QString name)
{    
    QVariant result;
    receive(name, result);
    return result;
}
    
void Script::scriptSend(QString name, QVariant value)
{    
    send(name, value);
}
    
void Script::scriptAddInputPort(QString name)
{    
    addInputPort(name);
}
    
void Script::scriptAddOutputPort(QString name)
{    
    addOutputPort(name);
}
    
void Script::scriptSetSelfStarting(bool value)
{
    setSelfStarting(value);
}

void Script::scriptEcho(QString message)
{
    std::cout << message.toStdString() << std::endl;
}
