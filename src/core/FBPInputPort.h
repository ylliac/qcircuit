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

#include "FBPPort.h"
#include "BlockingQueue.h"

class FBPInputPort : public FBPPort{
    Q_OBJECT
        
public:
    FBPInputPort(QString name);
    virtual ~FBPInputPort();
    
    int size() const;
    QVariant pop();
    
    void initialize(QVariant value);
    
public slots:
    void onReceive(QVariant value);
    
signals:
    void received(QVariant value);
    
private:
    BlockingQueue<QVariant> receivedQueue;
    bool iip;
};

#include "BlockingQueue.cpp"

#endif	/* FBPINPUTPORT_H */

