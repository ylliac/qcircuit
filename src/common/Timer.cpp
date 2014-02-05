/* 
 * File:   Timer.cpp
 * Author: acailly
 * 
 * Created on 4 février 2014, 11:37
 */

#include "Timer.h"

#include <QtCore/QTime>

Timer::Timer()
: timer(NULL)
{
    createInOutFromMetadata();
}

Timer::~Timer()
{
    delete timer;
}

void Timer::Process_(DspSignalBus& inputs, DspSignalBus& outputs)
{
    if(timer == NULL){
        timer = new QTime();
        timer->start();
    }
    
    int elapsed = timer->elapsed();
    if(elapsed > 1000)
    {
        outputs.SetValue("TIME", elapsed);
        timer->start();
    }
}

