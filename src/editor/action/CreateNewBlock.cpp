/* 
 * File:   CreateNewBlock.cpp
 * Author: acailly
 * 
 * Created on 5 mars 2014, 15:51
 */

#include "CreateNewBlock.h"

#include <QtGui/QGraphicsScene>
#include <QtGui/QGraphicsTextItem>
#include <QtGui/QGraphicsEllipseItem>
#include <QtGui/QGraphicsRectItem>

#include "editor/FBPEditor.h"
#include "editor/scene/EditorScene.h"
#include "editor/scene/BlockItem.h"
#include "editor/scene/SceneDetective.h"

CreateNewBlock::CreateNewBlock(FBPEditor* editor) :
FBPEditorAction(editor)
{
}

CreateNewBlock::~CreateNewBlock()
{
}

void CreateNewBlock::execute(QString name, QString className, QString, QString, QString)
{           
    QGraphicsScene* scene = getEditor()->getScene();
        
    //Find a name that doesn't exists
    QString newName = SceneDetective::newUniqueNonEmptyBlockName(scene, name);
        
    //Create the block
    BlockItem* newBlock = new BlockItem(getEditor());
    scene->addItem(newBlock);    
    newBlock->setPos(200,10);
    newBlock->setName(newName);
    newBlock->setClassName(className);
}

