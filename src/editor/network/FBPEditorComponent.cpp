/* 
 * File:   FBPEditorComponent.cpp
 * Author: acailly
 * 
 * Created on 25 février 2014, 11:55
 */

#include "FBPEditorComponent.h"

#include "Util.h"
#include <iostream>

FBPEditorComponent::FBPEditorComponent()
{
    addInputPort("EDITOR");
}

FBPEditorComponent::~FBPEditorComponent()
{
}

void FBPEditorComponent::receiveEditor()
{    
    QVariant value = receive("EDITOR");        
    m_Editor = Util::toPointer<FBPEditor>(value);
}

FBPEditor* FBPEditorComponent::getEditor()
{
    return m_Editor;
}

