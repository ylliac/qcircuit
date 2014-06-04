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
    setObjectName(metaObject()->className());
    
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
    
    QVariant packet;
    while(receive("IN", packet))
    {
        //------------------------------------------------------------------
        // READ THE LINE
        //------------------------------------------------------------------
        int inData = packet.toInt();

        //------------------------------------------------------------------
        // SEND VIA UDP
        //------------------------------------------------------------------
        QByteArray datagram = QByteArray::number(inData);
        qint64 result = udpSocket->writeDatagram(
                datagram.data(),
                datagram.size(),
                QHostAddress::Broadcast,
                4444);
        Q_ASSERT(result != -1);

        //TODO ACY TEST LOG
        std::cout << "UDPEmitter just sent the data: " << inData << std::endl;
    }
    
    //EOF
    QByteArray datagram;
    qint64 result = udpSocket->writeDatagram(
            datagram.data(),
            datagram.size(),
            QHostAddress::Broadcast,
            4444);
    Q_ASSERT(result != -1);
}

