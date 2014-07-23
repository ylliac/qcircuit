/* 
 * File:   Counter.cpp
 * Author: acailly
 * 
 * Created on 19 février 2014, 12:00
 */

#include "Counter.h"

#include <iostream>

Counter::Counter(QObject* parent)
: QObject(parent)
{
}

Counter::~Counter()
{
}

int Counter::count()
{
    return counter;
}

void Counter::increase()
{
    counter.ref();
}

void Counter::decrease()
{    
    bool isZero = !counter.deref();
    
    if(isZero){
        emit zero();
    }
}

