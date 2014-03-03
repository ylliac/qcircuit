/* 
 * File:   TextPrompt.cpp
 * Author: acailly
 * 
 * Created on 3 mars 2014, 15:21
 */

#include "TextPrompt.h"

#include "editor/FBPEditor.h"
#include "Util.h"

#include <QtGui/QInputDialog>

TextPrompt::TextPrompt()
: m_Item(NULL)
{
}

TextPrompt::~TextPrompt()
{
}

void TextPrompt::attachImpl()
{
    m_Item = new QInputDialog(getEditor());  
    m_Item->setWindowTitle("Prompt");
    m_Item->setLabelText("Enter value: ");
    m_Item->setTextValue("here");
    m_Item->setTextEchoMode(QLineEdit::Normal);
}
    
void TextPrompt::detachImpl()
{
    m_Item->setParent(NULL);
    delete m_Item;
    m_Item = NULL;
}

void TextPrompt::inTrigger(QVariant v)
{
    int ret = m_Item->exec();
    if (ret) {
        emit outValue(QVariant(m_Item->textValue()));
    } 
}

