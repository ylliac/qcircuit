/* 
 * File:   EditorScene.cpp
 * Author: acailly
 * 
 * Created on 5 mars 2014, 17:15
 */

#include "EditorScene.h"
#include "DefaultState.h"

#include <QtGui/QGraphicsSceneMouseEvent>

EditorScene::EditorScene(QObject* parent) :
QGraphicsScene(parent)
{
    //Background color
    setBackgroundBrush(QBrush(Qt::white));
    
    //State
    //installEventFilter(new DefaultState(this));
}

EditorScene::~EditorScene()
{
}



