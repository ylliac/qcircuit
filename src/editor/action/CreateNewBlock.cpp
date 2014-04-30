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

CreateNewBlock::CreateNewBlock(QGraphicsScene* scene) :
m_Scene(scene)
{
}

CreateNewBlock::~CreateNewBlock()
{
}

void CreateNewBlock::execute()
{    
    BlockItem* newBlock = new BlockItem();
    m_Scene->addItem(newBlock);    
    newBlock->setPos(200,10);
    
    BlockItem* newBlock2 = new BlockItem();
    m_Scene->addItem(newBlock2);       
    newBlock2->setPos(400,10);
    
//    QBrush greenBrush(Qt::green);
//    QBrush blueBrush(Qt::blue);
//    QPen outlinePen(Qt::black);
//    outlinePen.setWidth(2);
//    
//    QGraphicsRectItem* block = m_Scene->addRect(100, 0, 80, 100, outlinePen, blueBrush);
//    block->setFlag(QGraphicsItem::ItemIsMovable);
//    block->setFlag(QGraphicsItem::ItemIsSelectable);
    
//    QGraphicsRectItem* block2 = m_Scene->addRect(150, 0, 80, 100, outlinePen, greenBrush);
//    block2->setFlag(QGraphicsItem::ItemIsMovable);
//    block2->setFlag(QGraphicsItem::ItemIsSelectable);

//    // addEllipse(x,y,w,h,pen,brush)
//    QGraphicsEllipseItem* ellipse = m_Scene->addEllipse(0, -100, 300, 60, outlinePen, greenBrush);
//
//    QGraphicsTextItem* text = m_Scene->addText("bogotobogo.com", QFont("Arial", 20) );
//    // movable text
//    text->setFlag(QGraphicsItem::ItemIsMovable);
}

