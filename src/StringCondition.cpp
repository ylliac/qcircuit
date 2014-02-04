/* 
 * File:   StringCondition.cpp
 * Author: acailly
 * 
 * Created on 29 janvier 2014, 17:49
 */

#include "StringCondition.h"

#include <iostream>

StringCondition::StringCondition(QString expectedString)
: m_ExpectedString(expectedString)
{
    //------------------------------------------------------------------
    // INPUTS 
    //------------------------------------------------------------------
    AddInput_("IN");

    //------------------------------------------------------------------
    // OUTPUTS 
    //------------------------------------------------------------------
    AddOutput_("OUT");
}

StringCondition::~StringCondition()
{
}

void StringCondition::Process_(DspSignalBus& inputs, DspSignalBus& outputs)
{
    QString inData;
    QString outData;
    if (inputs.GetValue("IN", inData) 
            && !outputs.GetValue("OUT", outData))
    {
        //------------------------------------------------------------------
        // CHECK THE CONDITION
        //------------------------------------------------------------------
        bool pass = inData.contains(m_ExpectedString, Qt::CaseInsensitive);

        //------------------------------------------------------------------
        // LET THE DATA PASS
        //------------------------------------------------------------------
        if (pass)
        {
            outputs.SetValue("OUT", inData);
            
            //TODO ACY TEST LOG
//            std::cout << "StringCondition just sent the data: " << inData.toStdString() << std::endl;
        }
    }
}
