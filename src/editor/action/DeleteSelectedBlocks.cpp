/* 
 * File:   DeleteSelectedBlocks.cpp
 * Author: acailly
 * 
 * Created on 30 avril 2014, 11:20
 */

#include "DeleteSelectedBlocks.h"

#include "DeleteBlock.h"
#include "editor/scene/SceneDetective.h"

DeleteSelectedBlocks::DeleteSelectedBlocks(QGraphicsScene* scene) :
m_Scene(scene)
{
}

DeleteSelectedBlocks::~DeleteSelectedBlocks()
{
}

void DeleteSelectedBlocks::execute()
{    
    QList<BlockItem*> selectedBlocks = SceneDetective::getSelectedBlocks(m_Scene);
    foreach(BlockItem* block, selectedBlocks)
    {
        DeleteBlock deleteAction(block);
        deleteAction.execute();
    }
}

