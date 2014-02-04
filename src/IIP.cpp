/* 
 * File:   IIP.cpp
 * Author: acailly
 * 
 * Created on 3 février 2014, 14:15
 */

#include "IIP.h"

IIP::IIP()
{
    //------------------------------------------------------------------
    // INPUTS 
    //------------------------------------------------------------------
    //NONE

    //------------------------------------------------------------------
    // OUTPUTS 
    //------------------------------------------------------------------
    AddOutput_("OUT");
    
    sent = false;
}

IIP::~IIP()
{
}

void IIP::Process_(DspSignalBus& inputs, DspSignalBus& outputs)
{
    if(!sent)
    {
        outputs.SetValue("OUT", 12);
        sent = true;
    }
}
