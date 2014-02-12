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

UDPEmitter::UDPEmitter()
{
    createInOutFromMetadata();    
    
    udpSocket = new QUdpSocket();
}

UDPEmitter::~UDPEmitter()
{
    delete udpSocket;
}

void UDPEmitter::Process_(DspSignalBus& inputs, DspSignalBus& outputs)
{
    //------------------------------------------------------------------
    // READ THE LINE
    //------------------------------------------------------------------
    int inData;
    if (inputs.GetValue("IN", inData))
    {
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
//        std::cout << "UDPEmitter just sent the data: " << inData << std::endl;
    }
}

