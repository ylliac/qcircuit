/* 
 * File:   FBPComponent.h
 * Author: acailly
 *
 * Created on 13 fÃ©vrier 2014, 18:17
 */

#ifndef FBPCOMPONENT_H
#define	FBPCOMPONENT_H

#include <QtCore/QThread>
#include <QtCore/QQueue>
#include <QtCore/QVariant>

#include "FBPInputPort.h"
#include "FBPOutputPort.h"

class FBPComponent : public QThread {
    Q_OBJECT
    
public:
    FBPComponent();
    virtual ~FBPComponent();
        
    FBPInputPort* addInputPort(QString name);
    FBPOutputPort* addOutputPort(QString name);
    
    FBPInputPort* getInputPort(QString name);
    FBPOutputPort* getOutputPort(QString name);
    
public slots:
    void activate();
    
protected:
    virtual void run();
    virtual void execute()=0;    
    
    QVariant receive(QString name);
    int received(QString name);
    void send(QString name, QVariant value);
        
private:
    QMap<QString, FBPInputPort*> inputPorts;
    QMap<QString, FBPOutputPort*> outputPorts;
        
};

//------------------------------------------------------------------
// MACROS 
//------------------------------------------------------------------

//SEND

#define FBP_SEND(outPortName, value) \
    send(#outPortName, value)

//RECEIVED

#define FBP_RECEIVED(inPortName) \
    received(#inPortName)

//RECEIVE

#define FBP_RECEIVE(inPortName) \
    receive(#inPortName)

//CONNECT

#define FBP_CONNECT(source, outPortName, target, inPortName) \
    connect(source->getOutputPort(#outPortName), SIGNAL(send(QVariant)), target->getInputPort(#inPortName), SLOT(receive(QVariant)))

#endif	/* FBPCOMPONENT_H */

