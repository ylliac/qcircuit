/* 
 * File:   UDPReceiver.h
 * Author: acailly
 *
 * Created on 3 février 2014, 17:01
 */

#ifndef UDPRECEIVER_H
#define	UDPRECEIVER_H

#include <dspatch/DspComponent.h>
#include <dspatch/DspSignalBus.h>

#include <QtCore/QObject>
#include <QtCore/QStack>

class QUdpSocket;

class UDPReceiver : public QObject, public DspComponent {
    Q_OBJECT
    
public:
    UDPReceiver();
    virtual ~UDPReceiver();

protected:
    virtual void Process_(DspSignalBus& inputs, DspSignalBus& outputs);
    
private slots:
    void processPendingDatagrams();
    
private:
    QUdpSocket* udpSocket;
    QStack<int> stack;
};

#endif	/* UDPRECEIVER_H */

