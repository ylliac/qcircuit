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
    AddOutput_("OUT");
}

ReadTextFile::~ReadTextFile()
{
}

void ReadTextFile::Process_(DspSignalBus& inputs, DspSignalBus& outputs)
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
    QString currentValue;
    bool hasValue = outputs.GetValue("OUT", currentValue);
    if (!m_FileContent.isEmpty() && !hasValue)
    {
        //------------------------------------------------------------------
        // Send the content 
        //------------------------------------------------------------------
        QString outputValue = m_FileContent.first();
        outputs.SetValue("OUT", outputValue);
        m_FileContent.removeFirst();
        
        //TODO ACY TEST LOG
//        std::cout << "ReadTextFile just sent the line: " << outputValue.toStdString() << std::endl;
    }
}
