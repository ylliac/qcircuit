/* 
 * File:   UDPReceiver.h
 * Author: acailly
 *
 * Created on 3 février 2014, 17:01
 */

#ifndef UDPRECEIVER_H
#define	UDPRECEIVER_H

#include "../core/FBPComponent.h"

#include <QtCore/QObject>
#include <QtCore/QStack>

class QUdpSocket;

class UDPReceiver : public FBPComponent{
    Q_OBJECT
    
public:    
    Q_INVOKABLE UDPReceiver();
    virtual ~UDPReceiver();

protected:
    virtual void execute();
    
private slots:
    void processPendingDatagrams();
    
private:
    QUdpSocket* udpSocket;
    QStack<QVariant> stack;
};

#endif	/* UDPRECEIVER_H */

