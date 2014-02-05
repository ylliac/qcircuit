/* 
 * File:   Timer.h
 * Author: acailly
 *
 * Created on 4 février 2014, 11:37
 */

#ifndef TIMER_H
#define	TIMER_H

#include "../core/QComponent.h"

#include <QtCore/QMetaType>

class QTime;

class Timer : public QComponent{
    Q_OBJECT
    Q_CLASSINFO("TIME", "OUT")
    
public:
    
    Timer();
    virtual ~Timer();
    
protected:
    virtual void Process_(DspSignalBus& inputs, DspSignalBus& outputs);
    
private:
    QTime* timer;
};

#endif	/* TIMER_H */

