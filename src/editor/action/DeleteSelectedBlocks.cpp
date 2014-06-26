/* 
 * File:   DeleteSelectedBlocks.cpp
 * Author: acailly
 * 
 * Created on 30 avril 2014, 11:20
 */

#include "DeleteSelectedBlocks.h"

#include <QtGui/QGraphicsScene>

#include "DeleteBlock.h"
#include "editor/FBPEditor.h"
#include "editor/scene/EditorScene.h"
#include "editor/scene/SceneDetective.h"

DeleteSelectedBlocks::DeleteSelectedBlocks(FBPEditor* editor) :
FBPEditorAction(editor)
{
}

DeleteSelectedBlocks::~DeleteSelectedBlocks()
{
}

void DeleteSelectedBlocks::execute(QString, QString, QString, QString, QString)
{    
    QGraphicsScene* scene = getEditor()->getScene();
      
    QList<BlockItem*> selectedBlocks = SceneDetective::getSelectedBlocks(scene);
    foreach(BlockItem* block, selectedBlocks)
    {
        getEditor()->runScriptCommand(
            QString("Delete the block %1")
            .arg(block->name())
            );        
    }
}

