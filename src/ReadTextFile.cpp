/* 
 * File:   ReadTextFile.cpp
 * Author: acailly
 * 
 * Created on 29 janvier 2014, 17:15
 */

#include "ReadTextFile.h"

#include <iostream>

#include <QtCore/QFile>
#include <QtCore/QIODevice>
#include <QtCore/QTextStream>

ReadTextFile::ReadTextFile(QString filePath)
: m_FilePath(filePath), m_Trigger(true)
{
    //------------------------------------------------------------------
    // INPUTS 
    //------------------------------------------------------------------
    //NONE

    //------------------------------------------------------------------
    // OUTPUTS 
    //------------------------------------------------------------------
    addOutputPort("OUT");
    
    setSelfStarting(true);
}

ReadTextFile::~ReadTextFile()
{
}

void ReadTextFile::execute()
{
    //------------------------------------------------------------------
    // READ THE FILE CONTENT 
    //------------------------------------------------------------------
    if (m_Trigger)
    {
        m_Trigger = false;
        m_FileContent.clear();

        QString content;
        QFile inputFile(m_FilePath);
        if (inputFile.exists() && inputFile.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QTextStream stream(&inputFile);
            while (!stream.atEnd())
            {
                QString line = stream.readLine();
                m_FileContent.append(line);
            }
            inputFile.close();
        }
    }

    //------------------------------------------------------------------
    // SEND LINES ONE BY ONE 
    //------------------------------------------------------------------
    if (!m_FileContent.isEmpty())
    {
        //------------------------------------------------------------------
        // Send the content 
        //------------------------------------------------------------------
        QString outputValue = m_FileContent.first();
        send("OUT", outputValue);
        m_FileContent.removeFirst();
        
        //TODO ACY TEST LOG
//        std::cout << "ReadTextFile just sent the line: " << outputValue.toStdString() << std::endl;
    }
}
