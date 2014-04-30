/* 
 * File:   SetBlockName.cpp
 * Author: acailly
 * 
 * Created on 30 avril 2014, 11:34
 */

#include "SetBlockName.h"

#include "editor/scene/BlockItem.h"

SetBlockName::SetBlockName(BlockItem* block, QString name):
m_Block(block),
m_Name(name)
{
}

SetBlockName::~SetBlockName()
{
}

void SetBlockName::execute()
{    
    if(m_Block != NULL)
    {
        m_Block->setName(m_Name);
    }
}

