/* 
 * File:   CreateNewBlock.cpp
 * Author: acailly
 * 
 * Created on 25 février 2014, 11:44
 */

#include "CreateNewComponent.h"

#include "editor/FBPEditor.h"
#include "util/GUIThreadExecutor.h"

#include <QtCore/QThread>
#include <QtGui/QApplication>
#include <QtGui/QGraphicsScene>
#include <QtGui/QGraphicsRectItem>

CreateNewComponent::CreateNewComponent()
{
    addInputPort("NAME");
}

CreateNewComponent::~CreateNewComponent()
{
}

void CreateNewComponent::execute()
{
    receiveEditor();

    QVariant name;
    while (receive("NAME", name))
    {
        m_Name = name.toString();
        
        GUIThreadExecutor executor;
        executor.execute(this, "uiCreateRect", true);
    }
}

void CreateNewComponent::uiCreateRect()
{    
    QGraphicsRectItem* block = getEditor()->getScene()->addRect(20, 20, 20, 20);
    block->setToolTip(m_Name);
}

