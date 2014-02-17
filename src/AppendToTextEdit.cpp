/* 
 * File:   AppendToTextEdit.cpp
 * Author: acailly
 * 
 * Created on 29 janvier 2014, 18:14
 */

#include "AppendToTextEdit.h"

#include <iostream>

#include <QtCore/QString>
#include <QtCore/QMetaObject>
#include <QtGui/QListWidget>

AppendToTextEdit::AppendToTextEdit(QListWidget* textEdit)
: m_TextEdit(textEdit)
{
    //------------------------------------------------------------------
    // INPUTS 
    //------------------------------------------------------------------
    addInputPort("IN");

    //------------------------------------------------------------------
    // OUTPUTS 
    //------------------------------------------------------------------
    //NONE
}

AppendToTextEdit::~AppendToTextEdit()
{
}

void AppendToTextEdit::execute()
{
    QString inData = receive("IN").toString();
    m_TextEdit->addItem(inData);    
        
    //TODO ACY TEST LOG
    std::cout << "AppendToTextEdit just dispayed the data: " << inData.toStdString() << std::endl;    
}

