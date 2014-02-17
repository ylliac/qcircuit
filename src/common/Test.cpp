/* 
 * File:   Test.cpp
 * Author: acailly
 * 
 * Created on 14 février 2014, 11:20
 */

#include "Test.h"

#include <iostream>

Test::Test()
{
    addInputPort("IN");
    addOutputPort("OUT");
}

Test::~Test()
{
}

void Test::execute()
{
    while (true)
    {
        QVariant value = receive("IN");
        
        std::cout << "RECEIVED: " << value.toString().toStdString() << std::endl;

        send("OUT", value);
    }
}
