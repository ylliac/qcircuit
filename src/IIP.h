/* 
 * File:   IIP.h
 * Author: acailly
 *
 * Created on 3 février 2014, 14:15
 */

#ifndef IIP_H
#define	IIP_H

#include <dspatch/DspComponent.h>
#include <dspatch/DspSignalBus.h>

class IIP : public DspComponent{
public:
    IIP();
    virtual ~IIP();
    
protected:
    virtual void Process_(DspSignalBus& inputs, DspSignalBus& outputs);
    
private:
    bool sent;

};

#endif	/* IIP_H */

