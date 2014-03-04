/* 
 * File:   Connector.cpp
 * Author: acailly
 * 
 * Created on 3 mars 2014, 18:21
 */

#include "Connector.h"

Connector::Connector()
{
    addInputPort("IN");
    addOutputPort("OUT");
}

Connector::~Connector()
{
}

void Connector::execute()
{
    QVariant data;
    while (receive("IN", data))
    {
        emit out(data);
    }
}

void Connector::in(QVariant v)
{
    send("OUT", v);
}

