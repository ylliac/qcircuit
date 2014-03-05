/* 
 * File:   FBPEditorAction.cpp
 * Author: acailly
 * 
 * Created on 3 mars 2014, 18:32
 */

#include "FBPEditorAction.h"

FBPEditorAction::FBPEditorAction(FBPEditor* parent)
: QObject(parent), m_Editor(parent)
{
}

FBPEditorAction::~FBPEditorAction()
{
}

FBPEditor* FBPEditorAction::getEditor() const
{
    return m_Editor;
}

