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
 
    //TODO ACY
//    std::cout << "[LOG] " << "Execute component " << metaObject()->className() << std::endl;   
    
    if(timer == NULL){
        timer = new QTime();
        timer->start();
    }
    
    while(true)
    {
        int elapsed = timer->elapsed();
        
        if(elapsed > 1000)
        {
            send("TIME", elapsed);
            timer->start();
            
            
            //TODO ACY
            std::cout << "Timer sent " << elapsed << std::endl; 
        }
    }
    
    //TODO ACY
//    std::cout << "[LOG] " << "Terminate component " << metaObject()->className() << std::endl;    
}

