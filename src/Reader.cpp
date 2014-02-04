/* 
 * File:   Reader.cpp
 * Author: acailly
 * 
 * Created on 3 février 2014, 12:17
 */

#include "Reader.h"

#include <iostream>

Reader::Reader()
{
    //------------------------------------------------------------------
    // INPUTS 
    //------------------------------------------------------------------
    AddInput_("IN");

    //------------------------------------------------------------------
    // OUTPUTS 
    //------------------------------------------------------------------
    //NONE
    
    m_Timer.start();
}

Reader::~Reader()
{
}

void Reader::Process_(DspSignalBus& inputs, DspSignalBus& outputs)
{    
//    if(m_Timer.elapsed() > 5000)
//    {
    
//        std::cout << "Reader ticks!" << std::endl;        
        
        //------------------------------------------------------------------
        // READ 
        //------------------------------------------------------------------    
        int inValue = -1;
        if(inputs.GetValue("IN", inValue))
        {        
            //TODO ACY TEST LOG
            std::cout << "Reader just read the number: " << inValue << std::endl;        
        }
        
//    }
}
