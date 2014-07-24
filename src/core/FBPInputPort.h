/* 
 * File:   FBPInputPort.h
 * Author: acailly
 *
 * Created on 14 février 2014, 17:49
 */

#ifndef FBPINPUTPORT_H
#define	FBPINPUTPORT_H

#include <QtCore/QVariant>
#include <QtCore/QQueue>
#include <QtCore/QAtomicInt>

#include "FBPPort.h"
#include "BlockingQueue.h"

class FBPComponent;

class FBPInputPort : public FBPPort {
    Q_OBJECT

public:
    FBPInputPort(QString name, FBPComponent* parent);
    virtual ~FBPInputPort();

    int size() const;
    bool receive(QVariant& outData);

    void initialize(QVariant value);
    
    void increaseSenderCount();
    void decreaseSenderCount();
    
    //Drained: empty && closed
    bool isDrained();
    bool isEmpty();
    //Closed: sender count == 0
    bool isClosed();
    
    void send(QVariant value);

private:
    BlockingQueue<QVariant> receivedQueue;
    bool iip;

    FBPComponent* parent;
    
    int senderCount;
};

#include "BlockingQueue.cpp"

#endif	/* FBPINPUTPORT_H */

