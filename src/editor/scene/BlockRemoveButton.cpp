/* 
 * File:   BlockRemoveButton.cpp
 * Author: acailly
 * 
 * Created on 10 mars 2014, 11:10
 */

#include "BlockRemoveButton.h"
#include "BlockItem.h"
#include "SceneDetective.h"
#include "editor/action/DeleteBlock.h"

#include <QtCore/QEvent>
#include <QtGui/QPainter>
#include <QtGui/QMouseEvent>
#include <QtGui/QGraphicsView>
#include <QtGui/QGraphicsScene>
#include <QtGui/QGraphicsSceneMouseEvent>

BlockRemoveButton::BlockRemoveButton(QGraphicsItem *parent) :
m_Width(20),
m_Height(20)
{
    setParentItem(parent);
    setAcceptHoverEvents(true);

    m_Pen.setColor(Qt::white);
    m_Pen.setWidth(2);
    
    m_Brush.setColor(Qt::black);
    m_Brush.setStyle(Qt::SolidPattern);
    
    installSceneEventFilter(this);
}

BlockRemoveButton::~BlockRemoveButton()
{
}

QRectF BlockRemoveButton::boundingRect() const
{
    return QRectF(0, 0, m_Width, m_Height);
}

void BlockRemoveButton::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->setPen(m_Pen);
    painter->setBrush(m_Brush);
    
    QPointF topLeft(0, 0);
    QPointF bottomRight(m_Width, m_Height);
    QRectF rect(topLeft, bottomRight);
    painter->drawEllipse(rect);

    qreal widthPer4 = m_Width / 4.0;
    qreal heightPer4 = m_Height / 4.0;
    painter->drawLine(widthPer4, heightPer4, 3 * widthPer4, 3 * heightPer4);
    painter->drawLine(widthPer4, 3 * heightPer4, 3 * widthPer4, heightPer4);
}

void BlockRemoveButton::hoverLeaveEvent(QGraphicsSceneHoverEvent *)
{
    m_Pen.setColor(Qt::white);
    this->update(0, 0, m_Width, m_Height);
}

void BlockRemoveButton::hoverEnterEvent(QGraphicsSceneHoverEvent *)
{
    m_Pen.setColor(QColor(255,140,0));
    this->update(0, 0, m_Width, m_Height);
}

bool BlockRemoveButton::sceneEventFilter(QGraphicsItem * watched, QEvent * event)
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
        //If mouse press event is not handled, mouse released event is never emitted
        return true;
    }
    else if (event->type() == QEvent::GraphicsSceneMouseRelease)
    {
        QGraphicsSceneMouseEvent * mouseEvent = ((QGraphicsSceneMouseEvent *) event);
        if (mouseEvent->button() == Qt::LeftButton)
        {
            BlockItem* parentBlock = dynamic_cast<BlockItem*>(parentItem());
            if(parentBlock != NULL)
            {
                parentBlock->getEditor()->runScriptCommand(
                    QString("Delete the block %1")
                    .arg(parentBlock->name())
                );
                
                return true;
            }
        }
    }

    return false;
}

