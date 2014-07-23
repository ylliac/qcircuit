/* 
 * File:   IIP.cpp
 * Author: HOME
 * 
 * Created on 23 juillet 2014, 20:44
 */

#include "IIP.h"

#include <iostream>
#include <QtCore/QVariant>

IIP::IIP(QList<QVariant> packets)
{
    this->packets.append(packets);
    
    setObjectName(metaObject()->className());

    addOutputPort("OUT");
    
    setSelfStarting(true);
}

IIP::~IIP() 
{
}

void IIP::execute()
{    
    while(this->packets.size() > 0)
    {
        QVariant packet = packets.dequeue();
        send("OUT", packet);
    }
}

