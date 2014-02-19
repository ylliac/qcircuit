/* 
 * File:   Timer.cpp
 * Author: acailly
 * 
 * Created on 4 février 2014, 11:37
 */

#include "Timer.h"

#include <iostream>
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
    
    int packetCount = 0;
    
    while(packetCount < 5)
    {
        int elapsed = timer->elapsed();
        
        if(elapsed > 1000)
        {
            send("TIME", elapsed);
            timer->start();
            
            
            //TODO ACY
            std::cout << "Timer sent " << elapsed << std::endl; 
            
            packetCount++;
        }
    }  
    
    //EOF
    send("TIME", QVariant());
}

