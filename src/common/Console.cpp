/* 
 * File:   Console.cpp
 * Author: acailly
 * 
 * Created on 4 février 2014, 11:46
 */

#include "Console.h"

#include <iostream>

Console::Console()
{
    createInOutFromMetadata();
}

Console::~Console()
{
}

void Console::Process_(DspSignalBus& inputs, DspSignalBus& outputs)
{
    QString output;
    
    int integer;
    if(inputs.GetValue("MESSAGE", integer)){
        output = QString::number(integer);
    }
    
    if(!output.isEmpty())
    {
        std::cout << "Console: " << output.toStdString() << std::endl;
    }
}

