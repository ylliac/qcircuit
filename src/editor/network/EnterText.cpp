/* 
 * File:   EnterText.cpp
 * Author: acailly
 * 
 * Created on 25 février 2014, 12:25
 */

#include "EnterText.h"
#include "util/GUIThreadExecutor.h"

#include <iostream>
#include <QtCore/QThread>

#include <QtGui/QInputDialog>
#include <QtGui/QLineEdit>
#include <QtGui/QApplication>

EnterText::EnterText()
{
    addInputPort("TRIGGER");
    addOutputPort("TEXT");
}

EnterText::~EnterText()
{
}

void EnterText::execute()
{
    receiveEditor();
    
    QVariant trigger;
    while (receive("TRIGGER", trigger))
    {        
        m_Text.clear();
        
        GUIThreadExecutor executor;
        executor.execute(this, "uiPrompt", true);
        
        if (!m_Text.isEmpty())
        {
            send("TEXT", QVariant(m_Text));
        }
    }
}

void EnterText::uiPrompt()
{    
    bool ok;    
    QString text = QInputDialog::getText(getEditor(), tr(""),
            tr(""), QLineEdit::Normal,
            "", &ok);
    if (ok && !text.isEmpty())
    {
        m_Text = text;
    }
}

