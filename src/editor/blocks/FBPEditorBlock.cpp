/* 
 * File:   FBPEditorBlock.cpp
 * Author: acailly
 * 
 * Created on 24 février 2014, 18:29
 */

#include "FBPEditorBlock.h"

#include "FBPEditor.h"

FBPEditorBlock::FBPEditorBlock()
: m_Editor(NULL)
{
}

FBPEditorBlock::~FBPEditorBlock()
{
}

void FBPEditorBlock::attach(FBPEditor* editor)
{
    Q_ASSERT(editor != NULL);
    Q_ASSERT(!isAttached());
    
    m_Editor = editor;
    
    attachImpl();
}
    
void FBPEditorBlock::detach()
{
    Q_ASSERT(isAttached());
    
    detachImpl();
    
    m_Editor = NULL;
}

bool FBPEditorBlock::isAttached()
{
    return m_Editor != NULL;
}

FBPEditor* FBPEditorBlock::getEditor()
{
    return m_Editor;
}

