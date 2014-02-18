/* 
 * File:   UDPEmitter.cpp
 * Author: acailly
 * 
 * Created on 3 février 2014, 16:36
 */

#include "UDPEmitter.h"

#include <iostream>

#include <QtNetwork/QUdpSocket>
#include <QtCore/QByteArray>
#include <QtCore/QVariant>

UDPEmitter::UDPEmitter()
{
    addInputPort("IN"); 
    
    udpSocket = NULL;
}

UDPEmitter::~UDPEmitter()
{
    delete udpSocket;
}

void UDPEmitter::execute()
{       
    
    if(udpSocket == NULL)
    {
        udpSocket = new QUdpSocket();
    }
    
    //------------------------------------------------------------------
    // READ THE LINE
    //------------------------------------------------------------------
    int inData = receive("IN").toInt();
    
    //------------------------------------------------------------------
    // SEND VIA UDP
    //------------------------------------------------------------------
    //TODO ACY
    QByteArray datagram = QByteArray::number(inData);
    udpSocket->writeDatagram(
            datagram.data(),
            datagram.size(),
            QHostAddress::Broadcast,
            4444);

    //TODO ACY TEST LOG
    std::cout << "UDPEmitter just sent the data: " << inData << std::endl;
}

