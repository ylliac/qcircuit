/* 
 * File:   DeleteBlock.cpp
 * Author: acailly
 * 
 * Created on 30 avril 2014, 11:22
 */

#include "DeleteBlock.h"

#include <QtGui/QGraphicsScene>

#include "editor/FBPEditor.h"
#include "editor/scene/EditorScene.h"
#include "editor/scene/ArrowItem.h"
#include "editor/scene/SceneDetective.h"

DeleteBlock::DeleteBlock(FBPEditor* editor) :
FBPEditorAction(editor)
{
}

DeleteBlock::~DeleteBlock()
{
}

void DeleteBlock::execute(QString blockName, QString, QString, QString, QString)
{    
    QGraphicsScene* scene = getEditor()->getScene();
    
    BlockItem* block = SceneDetective::getBlock(blockName, scene);
    if(block != NULL)
    {
        QGraphicsScene* scene = block->scene();
        
        //Delete connected arrows
        QList<ArrowItem*> connectedArrows = SceneDetective::getConnectedArrows(scene, block);
        foreach(ArrowItem* connectedArrow, connectedArrows)
        {
            scene->removeItem(connectedArrow);
        }
        //Delete parent block
        scene->removeItem(block);
    }
}

