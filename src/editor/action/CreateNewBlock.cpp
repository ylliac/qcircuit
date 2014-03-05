/* 
 * File:   CreateNewBlock.cpp
 * Author: acailly
 * 
 * Created on 5 mars 2014, 15:51
 */

#include "CreateNewBlock.h"
#include "editor/scene/BlockItem.h"

#include <QtGui/QGraphicsScene>
#include <QtGui/QGraphicsTextItem>
#include <QtGui/QGraphicsEllipseItem>
#include <QtGui/QGraphicsRectItem>

#include "editor/scene/EditorScene.h"

CreateNewBlock::CreateNewBlock(FBPEditor* parent)
: FBPEditorAction(parent)
{
}

CreateNewBlock::~CreateNewBlock()
{
}

void CreateNewBlock::execute()
{
    QGraphicsScene* scene = getEditor()->getScene();
    
    BlockItem* newBlock = new BlockItem();
    scene->addItem(newBlock);    
    
    BlockItem* newBlock2 = new BlockItem();
    scene->addItem(newBlock2);       
    
    QBrush greenBrush(Qt::green);
    QBrush blueBrush(Qt::blue);
    QPen outlinePen(Qt::black);
    outlinePen.setWidth(2);
    
    QGraphicsRectItem* block = scene->addRect(100, 0, 80, 100, outlinePen, blueBrush);
    block->setFlag(QGraphicsItem::ItemIsMovable);
    block->setFlag(QGraphicsItem::ItemIsSelectable);
    
//    QGraphicsRectItem* block2 = scene->addRect(150, 0, 80, 100, outlinePen, greenBrush);
//    block2->setFlag(QGraphicsItem::ItemIsMovable);
//    block2->setFlag(QGraphicsItem::ItemIsSelectable);

//    // addEllipse(x,y,w,h,pen,brush)
//    QGraphicsEllipseItem* ellipse = scene->addEllipse(0, -100, 300, 60, outlinePen, greenBrush);
//
//    QGraphicsTextItem* text = scene->addText("bogotobogo.com", QFont("Arial", 20) );
//    // movable text
//    text->setFlag(QGraphicsItem::ItemIsMovable);
}

