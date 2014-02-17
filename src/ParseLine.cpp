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
    addInputPort("LINE");

    //------------------------------------------------------------------
    // OUTPUTS 
    //------------------------------------------------------------------
    addOutputPort("KEY");
    addOutputPort("VALUE");
}

ParseLine::~ParseLine()
{
}

void ParseLine::execute()
{
    //------------------------------------------------------------------
    // READ THE LINE
    //------------------------------------------------------------------
    QString inLine = receive("LINE").toString();
    QString outKey = receive("KEY").toString();
        
    QStringList splittedLine = inLine.split("=");

    //------------------------------------------------------------------
    // SEND THE KEY AND THE VALUE 
    //------------------------------------------------------------------
    send("KEY", splittedLine.at(0));
    send("VALUE", splittedLine.at(1));

    //TODO ACY TEST LOG
//        std::cout << "ParseLine just sent the key: " << splittedLine.at(0).toStdString() << std::endl;
//        std::cout << "ParseLine just sent the value: " << splittedLine.at(1).toStdString() << std::endl;
}
