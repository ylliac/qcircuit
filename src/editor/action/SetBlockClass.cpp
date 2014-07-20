/* 
 * File:   SetBlockClass.cpp
 * Author: HOME
 * 
 * Created on 20 juillet 2014, 19:58
 */

#include "SetBlockClass.h"

#include <QtGui/QGraphicsScene>

#include "editor/FBPEditor.h"
#include "editor/scene/EditorScene.h"
#include "editor/scene/BlockItem.h"
#include "editor/scene/SceneDetective.h"

SetBlockClass::SetBlockClass(FBPEditor* editor) :
FBPEditorAction(editor)
{
}

SetBlockClass::~SetBlockClass()
{
}

void SetBlockClass::execute(QString blockName, QString className, QString, QString, QString)
{    
    QGraphicsScene* scene = getEditor()->getScene();
    
    BlockItem* block = SceneDetective::getBlock(blockName, scene);     
    if(block != NULL)
    {
        block->setClassName(className);            
    }
}

