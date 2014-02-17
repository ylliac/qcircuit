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
    addOutputPort("TIME");
    setSelfStarting(true);
}

Timer::~Timer()
{
    delete timer;
}

void Timer::execute()
{
    if(timer == NULL){
        timer = new QTime();
        timer->start();
    }
    
    while(true)
    {
        int elapsed = timer->elapsed();
        send("TIME", elapsed);
        
        sleep(1000);
    }
}

