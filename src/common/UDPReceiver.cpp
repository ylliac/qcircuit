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
    createInOutFromMetadata();
    
    udpSocket = new QUdpSocket();
    udpSocket->bind(4444, QUdpSocket::ShareAddress);
    
    connect(udpSocket, SIGNAL(readyRead()),this, SLOT(processPendingDatagrams()));
}

UDPReceiver::~UDPReceiver()
{
    delete udpSocket;
}

void UDPReceiver::Process_(DspSignalBus& inputs, DspSignalBus& outputs)
{
    if(!stack.isEmpty())
    {
        //------------------------------------------------------------------
        // SEND VIA UDP
        //------------------------------------------------------------------
        int outData = stack.pop();
        outputs.SetValue("OUT", outData);

        //TODO ACY TEST LOG
//        std::cout << "UDPReceiver just sent the data: " << outData << std::endl;
    }
}

void UDPReceiver::processPendingDatagrams()
{
    while (udpSocket->hasPendingDatagrams()) {
        QByteArray datagram;
        datagram.resize(udpSocket->pendingDatagramSize());
        udpSocket->readDatagram(datagram.data(), datagram.size());
        int value = datagram.toInt();
        stack.append(value);
    }
}

