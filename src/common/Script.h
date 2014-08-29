/* 
 * File:   Script.h
 * Author: acailly
 *
 * Created on 12 février 2014, 18:25
 */

#ifndef SCRIPT_H
#define	SCRIPT_H

#include "../core/FBPComponent.h"

#include <QtScript/QScriptEngine>
#include <QtScript/QScriptValue>
#include <QtScript/QScriptContext>

class Script : public FBPComponent {
    Q_OBJECT
    
public:
    Q_INVOKABLE Script(QString script);
    virtual ~Script();
    
    Q_INVOKABLE QVariant scriptReceive(QString name);
    Q_INVOKABLE void scriptSend(QString name, QVariant value);
    Q_INVOKABLE void scriptAddInputPort(QString name);
    Q_INVOKABLE void scriptAddOutputPort(QString name);
    Q_INVOKABLE void scriptSetSelfStarting(bool value);
    Q_INVOKABLE void scriptEcho(QString message);
    Q_INVOKABLE QVariant scriptReadFile(QString filePath);
    
protected:
    virtual void execute();
    
private:    
    QScriptEngine scriptEngine;
};

#endif	/* SCRIPT_H */

