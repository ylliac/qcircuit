/* 
 * File:   Dispatcher.h
 * Author: acailly
 *
 * Created on 29 janvier 2014, 17:59
 */

#ifndef DISPATCHER_H
#define	DISPATCHER_H

#include <dspatch/DspComponent.h>
#include <dspatch/DspSignalBus.h>

class Dispatcher : public DspComponent{
public:
    Dispatcher();
    virtual ~Dispatcher();
    
protected:
    virtual void Process_(DspSignalBus& inputs, DspSignalBus& outputs);

};

#endif	/* DISPATCHER_H */

