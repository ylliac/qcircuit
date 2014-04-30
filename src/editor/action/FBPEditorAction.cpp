/* 
 * File:   FBPEditorAction.cpp
 * Author: acailly
 * 
 * Created on 3 mars 2014, 18:32
 */

#include "FBPEditorAction.h"

FBPEditorAction::FBPEditorAction(FBPEditor* editor) :
QObject(editor),
m_Editor(editor)
{
}

FBPEditorAction::~FBPEditorAction()
{
}

FBPEditor* FBPEditorAction::getEditor()
{
    return m_Editor;
}
