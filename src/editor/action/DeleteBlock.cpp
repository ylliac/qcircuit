/* 
 * File:   DeleteBlock.cpp
 * Author: acailly
 * 
 * Created on 30 avril 2014, 11:22
 */

#include "DeleteBlock.h"

#include <QtGui/QGraphicsScene>

#include "editor/scene/ArrowItem.h"
#include "editor/scene/SceneDetective.h"

DeleteBlock::DeleteBlock(BlockItem* block) :
m_Block(block)
{
}

DeleteBlock::~DeleteBlock()
{
}

void DeleteBlock::execute()
{    
    if(m_Block != NULL)
    {
        QGraphicsScene* scene = m_Block->scene();
        
        //Delete connected arrows
        QList<ArrowItem*> connectedArrows = SceneDetective::getConnectedArrows(scene, m_Block);
        foreach(ArrowItem* connectedArrow, connectedArrows)
        {
            scene->removeItem(connectedArrow);
        }
        //Delete parent block
        scene->removeItem(m_Block);
    }
}

