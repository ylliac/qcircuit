/* 
 * File:   SetSelectedArrowToPortName.cpp
 * Author: HOME
 * 
 * Created on 14 juin 2014, 11:56
 */

#include "SetSelectedArrowToPortName.h"

#include <QtGui/QGraphicsScene>

#include "editor/FBPEditor.h"
#include "editor/scene/EditorScene.h"
#include "editor/scene/ArrowItem.h"
#include "editor/scene/SceneDetective.h"

SetSelectedArrowToPortName::SetSelectedArrowToPortName(FBPEditor* editor) :
FBPEditorAction(editor)
{
}

SetSelectedArrowToPortName::~SetSelectedArrowToPortName() {
}

void SetSelectedArrowToPortName::execute(QString portName, QString, QString, QString, QString)
{    
    QGraphicsScene* scene = getEditor()->getScene();
    
    QList<ArrowItem*> arrows = SceneDetective::getSelectedArrows(scene);     
    foreach(ArrowItem* arrow, arrows)
    {
        arrow->setInputPortName(portName);
    }
}

