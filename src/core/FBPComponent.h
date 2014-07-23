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
    enum State
    {
        NOT_STARTED,
        ACTIVATED,
        FINISHED
    };
    
public:
    FBPComponent(QObject* parent = NULL);
    virtual ~FBPComponent();
        
    FBPInputPort* addInputPort(QString name);
    FBPOutputPort* addOutputPort(QString name);
    
    FBPInputPort* getInputPort(QString name);
    FBPOutputPort* getOutputPort(QString name);
    
    bool isSelfStarting();
    
    bool isActive();
    bool isFinished();
    void wait();
    
public slots:
    void activate();
    
signals:
    void activated();
    void finished();
    
protected:
    virtual void execute()=0;    
    
    QVariant receive(QString name);
    bool receive(QString name, QVariant& outData);
    int received(QString name);
    void send(QString name, QVariant value);
    void close(QString name);
    
    void setSelfStarting(bool value);
        
private:
    void execute0();    
    
    QMap<QString, FBPInputPort*> inputPorts;
    QMap<QString, FBPOutputPort*> outputPorts;
    bool selfStarting;
    
    QFuture<void> future;
    State state;
};

#endif	/* FBPCOMPONENT_H */

