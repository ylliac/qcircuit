/* 
 * File:   Producer.cpp
 * Author: acailly
 * 
 * Created on 3 février 2014, 12:01
 */

#include "Producer.h"

#include <iostream>

#include <QtCore/QtGlobal>

Producer::Producer(int sleepTime)
:sleepTime(sleepTime)
{
    //------------------------------------------------------------------
    // INPUTS 
    //------------------------------------------------------------------
    //NONE

    //------------------------------------------------------------------
    // OUTPUTS 
    //------------------------------------------------------------------
    AddOutput_("OUT");
    
    m_Timer.start();
}

Producer::~Producer()
{
}

void Producer::Process_(DspSignalBus& inputs, DspSignalBus& outputs)
{
//    if(m_Timer.elapsed() < 1000)
//    {
        //TODO ACY TEST 
        int existingValue = -1;
        bool check = outputs.GetValue("OUT", existingValue);
//        std::cout << "Producer: existing value before? " << check << " => " << existingValue << std::endl;

        if(m_Timer.elapsed() > sleepTime) {
            m_Timer.start();
            
            //------------------------------------------------------------------
            // SEND A RAND NUMBER 
            //------------------------------------------------------------------
            int outputValue = qrand() % 100;
//            outputs.SetValue("OUT", outputValue);
            outputs.SetValue("OUT", sleepTime);

            //TODO ACY TEST LOG
//            std::cout << "Producer just sent the number: " << outputValue << std::endl;

            //TODO ACY TEST 
            existingValue = -1;
            check = outputs.GetValue("OUT", existingValue);
        //        std::cout << "Producer: existing value after? " << check << " => " << existingValue << std::endl;            
        }
//        Sleep(sleepTime);
        
        
//    }
}

