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
    QVariant inData;
    receive("IN", inData);
    m_TextEdit->addItem(inData.toString());    
        
    //TODO ACY TEST LOG
    std::cout << "AppendToTextEdit just dispayed the data: " << inData.toString().toStdString() << std::endl;    
}

