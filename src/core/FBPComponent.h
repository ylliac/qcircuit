/* 
 * File:   FBPComponent.h
 * Author: acailly
 *
 * Created on 13 fÃ©vrier 2014, 18:17
 */

#ifndef FBPCOMPONENT_H
#define	FBPCOMPONENT_H

#include <QtCore/QFuture>
#include <QtCore/QQueue>
#include <QtCore/QVariant>

#include "FBPInputPort.h"
#include "FBPOutputPort.h"

class FBPComponent : public QObject {
    Q_OBJECT
    
public:
    FBPComponent();
    virtual ~FBPComponent();
        
    FBPInputPort* addInputPort(QString name);
    FBPOutputPort* addOutputPort(QString name);
    
    FBPInputPort* getInputPort(QString name);
    FBPOutputPort* getOutputPort(QString name);
    
    bool isSelfStarting();
    
    bool isRunning();
    void wait();
    
public slots:
    void activate();
    
protected:
    virtual void execute()=0;    
    
    QVariant receive(QString name);
    int received(QString name);
    void send(QString name, QVariant value);
    
    void setSelfStarting(bool value);
        
private:
    QMap<QString, FBPInputPort*> inputPorts;
    QMap<QString, FBPOutputPort*> outputPorts;
    bool selfStarting;
    QFuture<void> future;
};

#endif	/* FBPCOMPONENT_H */

