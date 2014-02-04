/* 
 * File:   ParseLine.cpp
 * Author: acailly
 * 
 * Created on 29 janvier 2014, 17:40
 */

#include "ParseLine.h"

#include <iostream>

#include <QtCore/QString>
#include <QtCore/QStringList>

ParseLine::ParseLine()
{
    //------------------------------------------------------------------
    // INPUTS 
    //------------------------------------------------------------------
    AddInput_("LINE");

    //------------------------------------------------------------------
    // OUTPUTS 
    //------------------------------------------------------------------
    AddOutput_("KEY");
    AddOutput_("VALUE");
}

ParseLine::~ParseLine()
{
}

void ParseLine::Process_(DspSignalBus& inputs, DspSignalBus& outputs)
{
    //------------------------------------------------------------------
    // READ THE LINE
    //------------------------------------------------------------------
    QString inLine;
    QString outKey;
    if (inputs.GetValue("LINE", inLine) && !outputs.GetValue("KEY", outKey))
    {
        QStringList splittedLine = inLine.split("=");

        //------------------------------------------------------------------
        // SEND THE KEY AND THE VALUE 
        //------------------------------------------------------------------
        outputs.SetValue("KEY", splittedLine.at(0));
        outputs.SetValue("VALUE", splittedLine.at(1));
        
        //TODO ACY TEST LOG
//        std::cout << "ParseLine just sent the key: " << splittedLine.at(0).toStdString() << std::endl;
//        std::cout << "ParseLine just sent the value: " << splittedLine.at(1).toStdString() << std::endl;
    }
}
