/* 
 * File:   SceneDetective.cpp
 * Author: HOME
 * 
 * Created on 21 avril 2014, 11:36
 */

#include "SceneDetective.h"

QList<BlockItem*> SceneDetective::getBlocks(QGraphicsScene* scene)
{
    QList<BlockItem*> result;
            
    QList<QGraphicsItem*> items = scene->items();
    foreach(QGraphicsItem* item, items)
    {
        BlockItem* block = dynamic_cast<BlockItem*>(item);
        if(block != NULL)
        {
            result.append(block);
        }
    }
    
    return result;
}

QList<BlockItem*> SceneDetective::getSelectedBlocks(QGraphicsScene* scene)
{
    QList<BlockItem*> result;
            
    QList<QGraphicsItem*> items = scene->selectedItems();
    foreach(QGraphicsItem* item, items)
    {
        BlockItem* block = dynamic_cast<BlockItem*>(item);
        if(block != NULL)
        {
            result.append(block);
        }
    }
    
    return result;
}

QList<ArrowItem*> SceneDetective::getArrows(QGraphicsScene* scene)
{
    QList<ArrowItem*> result;
            
    QList<QGraphicsItem*> items = scene->items();
    foreach(QGraphicsItem* item, items)
    {
        ArrowItem* arrow = dynamic_cast<ArrowItem*>(item);
        if(arrow != NULL)
        {
            result.append(arrow);
        }
    }
    
    return result;
}
    
QList<ArrowItem*> SceneDetective::getConnectedArrows(QGraphicsScene* scene, BlockItem* block)
{
    QList<ArrowItem*> result;
    
    QList<ArrowItem*> arrows = getArrows(scene);
    foreach(ArrowItem* arrow, arrows){
        if(arrow->getStartBlock() == block || arrow->getEndBlock() == block)
        {
            result.append(arrow);
        }
    }
            
    return result;
}

