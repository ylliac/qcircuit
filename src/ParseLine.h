/* 
 * File:   ParseLine.h
 * Author: acailly
 *
 * Created on 29 janvier 2014, 17:40
 */

#ifndef PARSELINE_H
#define	PARSELINE_H

#include <dspatch/DspComponent.h>
#include <dspatch/DspSignalBus.h>

class ParseLine : public DspComponent{
public:
    ParseLine();
    virtual ~ParseLine();
    
protected:
    virtual void Process_(DspSignalBus& inputs, DspSignalBus& outputs);

};

#endif	/* PARSELINE_H */

