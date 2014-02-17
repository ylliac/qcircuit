/* 
 * File:   Timer.h
 * Author: acailly
 *
 * Created on 4 février 2014, 11:37
 */

#ifndef TIMER_H
#define	TIMER_H

#include "../core/FBPComponent.h"

#include <QtCore/QMetaType>

class QTime;

class Timer : public FBPComponent{
    Q_OBJECT
    
public:    
    Q_INVOKABLE Timer();
    virtual ~Timer();
    
protected:
    virtual void execute();
    
private:
    QTime* timer;
};

#endif	/* TIMER_H */

