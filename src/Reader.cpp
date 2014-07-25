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
    addInputPort("IN");

    //------------------------------------------------------------------
    // OUTPUTS 
    //------------------------------------------------------------------
    //NONE
}

Reader::~Reader()
{
}

void Reader::execute()
{    
    //------------------------------------------------------------------
    // READ 
    //------------------------------------------------------------------    
    QVariant inValue;
    receive("IN", inValue);
    
    //TODO ACY TEST LOG
    std::cout << "Reader just read the number: " << inValue.toInt() << std::endl;        
}
