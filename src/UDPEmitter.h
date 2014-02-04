/* 
 * File:   UDPEmitter.h
 * Author: acailly
 *
 * Created on 3 février 2014, 16:36
 */

#ifndef UDPEMITTER_H
#define	UDPEMITTER_H

#include <dspatch/DspComponent.h>
#include <dspatch/DspSignalBus.h>

class QUdpSocket;

class UDPEmitter : public DspComponent {
public:
    UDPEmitter();
    virtual ~UDPEmitter();

protected:
    virtual void Process_(DspSignalBus& inputs, DspSignalBus& outputs);
    
private:
    QUdpSocket* udpSocket;
};

#endif	/* UDPEMITTER_H */

