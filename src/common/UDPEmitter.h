/* 
 * File:   UDPEmitter.h
 * Author: acailly
 *
 * Created on 3 février 2014, 16:36
 */

#ifndef UDPEMITTER_H
#define	UDPEMITTER_H

#include "../core/FBPComponent.h"

class QUdpSocket;

class UDPEmitter : public FBPComponent{
    Q_OBJECT
    
public:    
    Q_INVOKABLE UDPEmitter();
    virtual ~UDPEmitter();

protected:
    virtual void execute();
    
private:
    QUdpSocket* udpSocket;
};

#endif	/* UDPEMITTER_H */

