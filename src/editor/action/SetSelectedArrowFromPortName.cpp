/* 
 * File:   SetSelectedArrowFromPortName.cpp
 * Author: HOME
 * 
 * Created on 14 juin 2014, 11:41
 */

#include "SetSelectedArrowFromPortName.h"

#include <QtGui/QGraphicsScene>

#include "editor/FBPEditor.h"
#include "editor/scene/EditorScene.h"
#include "editor/scene/ArrowItem.h"
#include "editor/scene/SceneDetective.h"

SetSelectedArrowFromPortName::SetSelectedArrowFromPortName(FBPEditor* editor) :
FBPEditorAction(editor)
{
}

SetSelectedArrowFromPortName::~SetSelectedArrowFromPortName() {
}

void SetSelectedArrowFromPortName::execute(QString portName, QString, QString, QString, QString)
{    
    QGraphicsScene* scene = getEditor()->getScene();
    
    QList<ArrowItem*> arrows = SceneDetective::getSelectedArrows(scene);     
    foreach(ArrowItem* arrow, arrows)
    {
        arrow->setOutputPortName(portName);
    }
}

