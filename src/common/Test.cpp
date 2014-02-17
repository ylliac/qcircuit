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
        QVariant value = FBP_RECEIVE(IN);
        
        std::cout << "RECEIVED: " << value.toString().toStdString() << std::endl;

        FBP_SEND(OUT, value);
    }
}
