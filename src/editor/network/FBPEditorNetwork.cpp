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
#include "editor/network/CreateNewComponent.h"
#include "Util.h"

FBPEditorNetwork::FBPEditorNetwork(FBPEditor* editor)
: m_Editor(editor)
{
    addInputPort("TRIGGER");
    addInputPort("NEWCOMPONENT_NAME");
    
    addOutputPort("NEWCOMPONENT_ASKNAME");
}

FBPEditorNetwork::~FBPEditorNetwork()
{
}

void FBPEditorNetwork::define()
{    
    bool check;
    
    QVariant editor = Util::toQVariant(m_Editor);
            
    CreateNewComponent* createNewComponent = new CreateNewComponent();
    addComponent(createNewComponent, "Create new component");
    initialize(editor, createNewComponent, "EDITOR");
    check = connectSubIn("NEWCOMPONENT_NAME", createNewComponent, "NAME");
    Q_ASSERT(check);
    
    check = connectSubInToOut("TRIGGER", "NEWCOMPONENT_ASKNAME");
    Q_ASSERT(check);
}

