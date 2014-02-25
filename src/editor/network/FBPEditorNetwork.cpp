/* 
 * File:   FBPEditorNetwork.cpp
 * Author: acailly
 * 
 * Created on 25 février 2014, 14:03
 */

#include "FBPEditorNetwork.h"

#include <iostream>

#include "editor/blocks/FBPEditorBlock.h"
#include "editor/FBPEditor.h"
#include "editor/network/EnterText.h"
#include "editor/network/CreateNewComponent.h"
#include "Util.h"

FBPEditorNetwork::FBPEditorNetwork(FBPEditor* editor)
: m_Editor(editor)
{
}

FBPEditorNetwork::~FBPEditorNetwork()
{
}

void FBPEditorNetwork::define()
{    
    QVariant editor = Util::toQVariant(m_Editor);
    
    FBPEditorBlock* newButton = m_Editor->getBlock("New block");
    
    EnterText* enterComponentName = new EnterText();
    addComponent(enterComponentName, "Enter component name");
    initialize(editor, enterComponentName, "EDITOR");
    connectFromSignal(newButton, SIGNAL(outClicked(QVariant)), enterComponentName, "TRIGGER");
    
    CreateNewComponent* createNewComponent = new CreateNewComponent();
    addComponent(createNewComponent, "Create new component");
    initialize(editor, createNewComponent, "EDITOR");
    connect(enterComponentName, "TEXT", createNewComponent, "NAME");
}

