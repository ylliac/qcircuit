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

class FBPInputPort;
class FBPOutputPort;
class FBPComponentListener;

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
    void setSelfStarting(bool value);
    
    bool isActive();
    bool isFinished();
    void wait();
    
    void activate();
    
    void addListener(FBPComponentListener* listener);
    void removeListener(FBPComponentListener* listener);
    
protected:
    virtual void execute()=0;    
    
    QVariant receive(QString name);
    bool receive(QString name, QVariant& outData);
    int received(QString name);
    void send(QString name, QVariant value);
    void close(QString name);
        
private:
    void execute0();    
    
    QMap<QString, FBPInputPort*> inputPorts;
    QMap<QString, FBPOutputPort*> outputPorts;
    bool selfStarting;
    
    QFuture<void> future;
    State state;
    
    QSet<FBPComponentListener*> listeners;
};

#endif	/* FBPCOMPONENT_H */

