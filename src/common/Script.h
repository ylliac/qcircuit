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
    Q_INVOKABLE Script();
    virtual ~Script();
    
    Q_INVOKABLE QVariant receiveValue(QString name);
    Q_INVOKABLE void sendValue(QString name, QVariant value);
    
protected:
    virtual void execute();
    
private:    
    QScriptEngine scriptEngine;
};

#endif	/* SCRIPT_H */

