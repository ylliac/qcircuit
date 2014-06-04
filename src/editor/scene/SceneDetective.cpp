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

BlockItem* SceneDetective::getBlock(QString name, QGraphicsScene* scene)
{
    BlockItem* result = NULL;
    
    QList<BlockItem*> blocks = getBlocks(scene);
    
    foreach(BlockItem* block, blocks)
    {
        if(name.compare(block->name(), Qt::CaseInsensitive) == 0)
        {
            result = block;
            break;
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

QString SceneDetective::newUniqueNonEmptyBlockName(QGraphicsScene* scene, QString name)
{
    QString newName = name;
    if(newName.isEmpty())
    {
        newName = "Block";
    } 
    
    if(getBlock(newName, scene) != NULL)
    {
        newName = QString("%1%2").arg(newName);
        int index = 2;
        while(getBlock(newName.arg(index), scene) != NULL)
        {
            index++;
        }
        newName = newName.arg(index);
    }
    
    return newName;
}

