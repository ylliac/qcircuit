/* 
 * File:   UDPReceiver.cpp
 * Author: acailly
 * 
 * Created on 3 février 2014, 17:01
 */

#include "UDPReceiver.h"

#include <iostream>

#include <QtNetwork/QUdpSocket>
#include <QtCore/QByteArray>

UDPReceiver::UDPReceiver()
{
    setObjectName(metaObject()->className());
    
    addOutputPort("OUT");
    setSelfStarting(true);
    
    udpSocket = new QUdpSocket();
    udpSocket->bind(4444, QUdpSocket::ShareAddress);
    
    bool check = connect(udpSocket, SIGNAL(readyRead()),this, SLOT(processPendingDatagrams()));
    Q_ASSERT(check);
}

UDPReceiver::~UDPReceiver()
{
    delete udpSocket;
}

void UDPReceiver::execute()
{
    bool exit = false;
    
    while(!exit)
    {
        if(!stack.isEmpty())
        {
            QVariant outData = stack.pop();
            
            if(outData.isValid())
            {            
                //------------------------------------------------------------------
                // SEND VIA UDP
                //------------------------------------------------------------------
                send("OUT", QVariant(outData.toInt()));

                //TODO ACY TEST LOG
                std::cout << "UDPReceiver just transmit the data: " << outData.toInt() << std::endl;
            }
            else
            {
                send("OUT", QVariant());
                exit = true;
            }
        }
    }
}

void UDPReceiver::processPendingDatagrams()
{
    while (udpSocket->hasPendingDatagrams()) {
        QByteArray datagram;
        datagram.resize(udpSocket->pendingDatagramSize());
        udpSocket->readDatagram(datagram.data(), datagram.size());
        
        if(datagram.isEmpty())
        {
            QVariant value;
            stack.append(value);
        }
        else
        {
            QVariant value(datagram.toInt());
            stack.append(value);
        }
    }
}

