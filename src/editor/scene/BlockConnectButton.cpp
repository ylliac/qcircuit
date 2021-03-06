/* 
 * File:   BlockConnectButton.cpp
 * Author: acailly
 * 
 * Created on 10 mars 2014, 17:24
 */

#include "BlockConnectButton.h"
#include "BlockItem.h"
#include "ArrowItem.h"
#include "editor/FBPEditor.h"

#include <QtCore/QEvent>
#include <QtGui/QPainter>
#include <QtGui/QMouseEvent>
#include <QtGui/QGraphicsView>
#include <QtGui/QGraphicsScene>
#include <QtGui/QGraphicsSceneMouseEvent>

#include <iostream>

BlockConnectButton::BlockConnectButton(QGraphicsItem *parent) :
m_Width(22),
m_Height(22),
m_Arrow(NULL)
{
    setParentItem(parent);
    setAcceptHoverEvents(true);

    m_Pen.setColor(Qt::white);
    m_Pen.setWidth(2);
    
    m_Brush.setColor(Qt::black);
    m_Brush.setStyle(Qt::SolidPattern);
    
    installSceneEventFilter(this);
}

BlockConnectButton::~BlockConnectButton()
{
}

QRectF BlockConnectButton::boundingRect() const
{
    return QRectF(0, 0, m_Width, m_Height);
}

void BlockConnectButton::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{    
    painter->setPen(m_Pen);
    painter->setBrush(m_Brush);
    
    QPointF topLeft(0, 0);
    QPointF bottomRight(m_Width, m_Height);
    QRectF rect(topLeft, bottomRight);
    painter->drawEllipse(rect);
    
    qreal widthPer4 = m_Width / 4.0;
    qreal heightPer4 = m_Height / 4.0;
    painter->drawLine(widthPer4, 2 * heightPer4, 3 * widthPer4, 2 * heightPer4);
    painter->drawLine(3 * widthPer4, 2 * heightPer4, 2 * widthPer4, heightPer4);
    painter->drawLine(3 * widthPer4, 2 * heightPer4, 2 * widthPer4, 3 * heightPer4);
}

void BlockConnectButton::hoverLeaveEvent(QGraphicsSceneHoverEvent *)
{
    m_Pen.setColor(Qt::white);
    this->update(0, 0, m_Width, m_Height);
}

void BlockConnectButton::hoverEnterEvent(QGraphicsSceneHoverEvent *)
{
    m_Pen.setColor(QColor(255,140,0));
    this->update(0, 0, m_Width, m_Height);
}

bool BlockConnectButton::sceneEventFilter(QGraphicsItem * watched, QEvent * event)
{
    if (watched != this)
    {
        // not expected to get here
        return false;
    }

    QGraphicsSceneMouseEvent * mevent = dynamic_cast<QGraphicsSceneMouseEvent*> (event);
    if (mevent == NULL)
    {
        // this is not one of the mouse events we are interrested in
        return false;
    }

    if (event->type() == QEvent::GraphicsSceneMousePress)
    {
        QGraphicsSceneMouseEvent * mouseEvent = ((QGraphicsSceneMouseEvent *) event);
        if (mouseEvent->button() == Qt::LeftButton)
        {
            m_Arrow = new QGraphicsLineItem(QLineF(mouseEvent->scenePos(), mouseEvent->scenePos()));
            m_Arrow->setPen(QPen(Qt::black, 2));
            scene()->addItem(m_Arrow);

            return true;
        }
    }
    else if (event->type() == QEvent::GraphicsSceneMouseMove)
    {
        QGraphicsSceneMouseEvent * mouseEvent = ((QGraphicsSceneMouseEvent *) event);
        if (m_Arrow != NULL)
        {
            QLineF newLine(m_Arrow->line().p1(), mouseEvent->scenePos());
            m_Arrow->setLine(newLine);

            return true;
        }
    }
    else if (event->type() == QEvent::GraphicsSceneMouseRelease)
    {
        QGraphicsSceneMouseEvent * mouseEvent = ((QGraphicsSceneMouseEvent *) event);
        if (mouseEvent->button() == Qt::LeftButton && m_Arrow != NULL)
        {
            QList<QGraphicsItem *> endItems = scene()->items(m_Arrow->line().p2(), Qt::IntersectsItemShape, Qt::AscendingOrder);
            endItems.removeAll(m_Arrow);

            scene()->removeItem(m_Arrow);
            delete m_Arrow;

            if (endItems.size() > 0)
            {
                BlockItem * startItem = dynamic_cast<BlockItem *>(parentItem());
                BlockItem * endItem = dynamic_cast<BlockItem *>(endItems.first());
                
                if(startItem != NULL && endItem != NULL)
                {                    
                    startItem->getEditor()->runScriptCommand(
                            QString("Create a new arrow from block %1 port %2 to block %3 port %4")
                            .arg(startItem->name())
                            .arg("OUT")
                            .arg(endItem->name())
                            .arg("IN")
                            );
                }
            }

            return true;
        }
        m_Arrow = NULL;
    }

    return false;
}

