/* 
 * File:   CreateNewArrow.cpp
 * Author: acailly
 * 
 * Created on 3 juin 2014, 19:02
 */

#include "CreateNewArrow.h"

#include <QtGui/QGraphicsScene>

#include "editor/FBPEditor.h"
#include "editor/scene/EditorScene.h"
#include "editor/scene/BlockItem.h"
#include "editor/scene/SceneDetective.h"

CreateNewArrow::CreateNewArrow(FBPEditor* editor) :
FBPEditorAction(editor)
{
}

CreateNewArrow::~CreateNewArrow()
{
}

void CreateNewArrow::execute(QString sourceBlockName, QString sourceBlockOutput, QString targetBlockName, QString targetBlockInput, QString)
{    
    QGraphicsScene* scene = getEditor()->getScene();

    BlockItem* sourceBlock = SceneDetective::getBlock(sourceBlockName, scene);
    if(sourceBlock == NULL)
    {
        getEditor()->info(QString("Can't find the block named %1").arg(sourceBlockName));
        return;
    }
    
    BlockItem* targetBlock = SceneDetective::getBlock(targetBlockName, scene);
    if(targetBlock == NULL)
    {
        getEditor()->info(QString("Can't find the block named %1").arg(targetBlockName));
        return;
    }
        
    ArrowItem* arrow = new ArrowItem(sourceBlock, targetBlock);
    arrow->setOutputPortName(sourceBlockOutput);
    arrow->setInputPortName(targetBlockInput);
    arrow->setColor(QColor(123, 229, 180)); //green
    //arrow->setColor(QColor(118,229,233)); //blue
    //arrow->setColor(QColor(248,131,128)); //red
    //arrow->setColor(QColor(132,130,250)); //violet
    //arrow->setColor(QColor(237,237,120)); //yellow
    //arrow->setColor(QColor(124,181,242)); //another blue
    //arrow->setColor(QColor(141,150,165)); //gray

    arrow->setZValue(-1000.0);
    scene->addItem(arrow);
    arrow->updateTextPosition();
}

