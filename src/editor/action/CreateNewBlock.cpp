/* 
 * File:   CreateNewBlock.cpp
 * Author: acailly
 * 
 * Created on 5 mars 2014, 15:51
 */

#include "CreateNewBlock.h"

#include <QtGui/QGraphicsScene>
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

void CreateNewBlock::execute(QString, QString, QString, QString, QString)
{    
    QGraphicsScene* scene = getEditor()->getScene();
    
    BlockItem* newBlock = new BlockItem(getEditor());
    scene->addItem(newBlock);    
    newBlock->setPos(200,10);
    
    //Set a name that doesn't exists
    QString name = "Block%1";
    int index = 1;
    while(SceneDetective::getBlock(name.arg(index), scene) != NULL)
    {
        index++;
    }
    newBlock->setName(name.arg(index));
}

