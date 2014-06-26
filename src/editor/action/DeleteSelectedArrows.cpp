/* 
 * File:   DeleteSelectedArrows.cpp
 * Author: HOME
 * 
 * Created on 14 juin 2014, 12:06
 */

#include "DeleteSelectedArrows.h"

#include <QtGui/QGraphicsScene>

#include "DeleteBlock.h"
#include "editor/FBPEditor.h"
#include "editor/scene/EditorScene.h"
#include "editor/scene/SceneDetective.h"

DeleteSelectedArrows::DeleteSelectedArrows(FBPEditor* editor) :
FBPEditorAction(editor)
{
}

DeleteSelectedArrows::~DeleteSelectedArrows()
{
}

void DeleteSelectedArrows::execute(QString, QString, QString, QString, QString)
{    
    QGraphicsScene* scene = getEditor()->getScene();
      
    QList<ArrowItem*> selectedArrows = SceneDetective::getSelectedArrows(scene);
    foreach(ArrowItem* arrow, selectedArrows)
    {
        //TODO ACY Comment identifier une arrow ?
//        getEditor()->runScriptCommand(
//            QString("Delete the arrow %1")
//            .arg(???)
//            );
        getEditor()->info("Deleting arrow is not implemented yet.");
    }
}

