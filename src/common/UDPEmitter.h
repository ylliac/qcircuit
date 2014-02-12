/* 
 * File:   UDPEmitter.h
 * Author: acailly
 *
 * Created on 3 février 2014, 16:36
 */

#ifndef UDPEMITTER_H
#define	UDPEMITTER_H

#include "../core/QComponent.h"

class QUdpSocket;

class UDPEmitter : public QComponent{
    Q_OBJECT
    Q_CLASSINFO("IN", "IN")
    
public:    
    Q_INVOKABLE UDPEmitter();
    virtual ~UDPEmitter();

protected:
    virtual void Process_(DspSignalBus& inputs, DspSignalBus& outputs);
    
private:
    QUdpSocket* udpSocket;
};

#endif	/* UDPEMITTER_H */

