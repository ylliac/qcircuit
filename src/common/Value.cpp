/* 
 * File:   Value.cpp
 * Author: acailly
 * 
 * Created on 23 juillet 2014, 18:27
 */

#include "Value.h"

#include <iostream>
#include <QtCore/QVariant>

Value::Value()
{
    setObjectName(metaObject()->className());

    addInputPort("IN");
    addOutputPort("OUT");
}

Value::~Value()
{
}

void Value::execute()
{    
    QVariant packet;
    while(receive("IN", packet))
    {
        set(packet);
    }
}

QVariant Value::get()
{
    return value;
}

void Value::set(QVariant value)
{
    this->value = value;
    send("OUT", value);
}

