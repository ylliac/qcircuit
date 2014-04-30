/* 
 * File:   SetBlockName.cpp
 * Author: acailly
 * 
 * Created on 30 avril 2014, 11:34
 */

#include "SetBlockName.h"

#include <QtGui/QGraphicsScene>

#include "editor/FBPEditor.h"
#include "editor/scene/EditorScene.h"
#include "editor/scene/BlockItem.h"
#include "editor/scene/SceneDetective.h"

SetBlockName::SetBlockName(FBPEditor* editor) :
FBPEditorAction(editor)
{
}

SetBlockName::~SetBlockName()
{
}

void SetBlockName::execute(QString blockName, QString newName, QString, QString, QString)
{    
    QGraphicsScene* scene = getEditor()->getScene();
    
    BlockItem* block = SceneDetective::getBlock(blockName, scene);     
    if(block != NULL)
    {
        //TODO ACY Ensure this name is not already taken
        
        block->setName(newName);
    }
}

