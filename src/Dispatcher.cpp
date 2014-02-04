/* 
 * File:   Dispatcher.cpp
 * Author: acailly
 * 
 * Created on 29 janvier 2014, 17:59
 */

#include "Dispatcher.h"

#include <iostream>

#include <QtCore/QString>

Dispatcher::Dispatcher()
{
    //------------------------------------------------------------------
    // INPUTS 
    //------------------------------------------------------------------
    AddInput_("IN");

    //------------------------------------------------------------------
    // OUTPUTS 
    //------------------------------------------------------------------
    //ADD ON DEMAND
}

Dispatcher::~Dispatcher()
{
}

void Dispatcher::Process_(DspSignalBus& inputs, DspSignalBus& outputs)
{
    //------------------------------------------------------------------
    // READ THE LINE
    //------------------------------------------------------------------

    //Check if all output ports have been consumed
    int outCount = outputs.GetSignalCount();
    int remainingOut = 0;
    for (int i = 0; i < outCount; i++)
    {
        QString value;
        bool hasValue = outputs.GetValue(i, value);
        if (hasValue)
        {
            remainingOut++;
        }
    }

    QString inData;
    if (inputs.GetValue("IN", inData) && remainingOut == 0)
    {
        for (int i = 0; i < outCount; i++)
        {
            outputs.SetValue(i, inData);
        }

        //TODO ACY TEST LOG
//        std::cout << "Dispatcher just sent the data: " << inData.toStdString() << std::endl;
    }
}



