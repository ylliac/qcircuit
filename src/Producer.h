/* 
 * File:   Producer.h
 * Author: acailly
 *
 * Created on 3 février 2014, 12:01
 */

#ifndef PRODUCER_H
#define	PRODUCER_H

#include <dspatch/DspComponent.h>
#include <dspatch/DspSignalBus.h>

#include <QtCore/QTime>

class Producer : public DspComponent{
public:
    Producer(int sleepTime = 0);
    virtual ~Producer();
    
protected:
    virtual void Process_(DspSignalBus& inputs, DspSignalBus& outputs);
    
private:
    QTime m_Timer;
    int sleepTime;

};

#endif	/* PRODUCER_H */

