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
#include <QtCore/QFile>

Script::Script(QString script)
{
    setObjectName(metaObject()->className());
    
    addOutputPort("ERROR");

    //From http://www.qtcentre.org/threads/10425-QtScript-newFunction-won-t-work
        
    QScriptValue that = scriptEngine.newQObject(this, QScriptEngine::QtOwnership, QScriptEngine::ExcludeChildObjects
		| QScriptEngine::ExcludeSuperClassMethods | QScriptEngine::ExcludeSuperClassProperties);
    scriptEngine.globalObject().setProperty("self",that);
    //Log in console
    scriptEngine.evaluate("function echo(str){self.scriptEcho(str);};");
    //Add input 
    scriptEngine.evaluate("function addInputPort(str){self.scriptAddInputPort(str);};");
    //Add output
    scriptEngine.evaluate("function addOutputPort(str){self.scriptAddOutputPort(str);};");
    //Set self starting
    scriptEngine.evaluate("function setSelfStarting(str){self.scriptSetSelfStarting(str);};");
    //Receive
    scriptEngine.evaluate("function receive(str){return self.scriptReceive(str);};");
    //Send
    scriptEngine.evaluate("function send(str, val){self.scriptSend(str, val);};");
    //Read file
    scriptEngine.evaluate("function readFile(str){return self.scriptReadFile(str);};");
    
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
    
    //Error handling
    if(scriptEngine.hasUncaughtException())
    {
        QScriptValue error = scriptEngine.uncaughtException();
        send("ERROR", error.toVariant());
    }
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

QVariant Script::scriptReadFile(QString filePath)
{
    QVariant result = QVariant(false);
    
    QFile file(filePath);
                
    if(file.exists())
    {
        QString data;
        if (file.open(QIODevice::ReadOnly)) {
            QTextStream in(&file);
            result = in.readAll();
            file.close();
        }
        else
        {
            send("ERROR", QString("Can't open file %1").arg(filePath));
        }
    }
    else
    {
        send("ERROR", QString("Can't find file %1").arg(filePath));
    }
    
    return result;
}
