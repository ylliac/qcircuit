/* 
 * File:   EditorScene.cpp
 * Author: acailly
 * 
 * Created on 5 mars 2014, 17:15
 */

#include "EditorScene.h"

#include <QtGui/QGraphicsSceneMouseEvent>

EditorScene::EditorScene(QObject* parent) :
QGraphicsScene(parent)
{
    //Background color
//    setBackgroundBrush(QBrush(Qt::white)); //white
//    setBackgroundBrush(QBrush(QColor(214,214,214))); // gray
    setBackgroundBrush(QBrush(QColor(245,245,245))); // light gray
    
    //State
    //installEventFilter(new DefaultState(this));
}

EditorScene::~EditorScene()
{
}



