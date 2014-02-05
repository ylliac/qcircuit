/* 
 * File:   QCircuit.cpp
 * Author: acailly
 * 
 * Created on 4 février 2014, 11:30
 */

#include "QCircuit.h"

#include <QtCore/QStringList>

QCircuit::QCircuit()
{
}

QCircuit::~QCircuit()
{
}

bool QCircuit::ConnectOutToIn(const QString& fromComponentAndPort, const QString& toComponentAndPort)
{
    // Parse input
    //------------------------------------------------------------------
    QStringList inputList = fromComponentAndPort.split(".");
    if (inputList.size() != 2)
    {
        return false;
    }

    std::string fromComponent = inputList.at(0).toStdString();
    std::string fromPort = inputList.at(1).toStdString();

    // Parse output
    //------------------------------------------------------------------
    QStringList outputList = toComponentAndPort.split(".");
    if (outputList.size() != 2)
    {
        return false;
    }

    std::string toComponent = outputList.at(0).toStdString();
    std::string toPort = outputList.at(1).toStdString();
    
    bool result = DspCircuit::ConnectOutToIn(fromComponent, fromPort, toComponent, toPort);
    return result;
}

