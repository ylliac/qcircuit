/* 
 * File:   BlockRemoveButton.cpp
 * Author: acailly
 * 
 * Created on 10 mars 2014, 11:10
 */

#include "BlockRemoveButton.h"

#include <QtGui/QPainter>

BlockRemoveButton::BlockRemoveButton(QGraphicsItem *parent) :
m_Width(20),
m_Height(20)
{
    setParentItem(parent);
    setAcceptHoverEvents(true);
    
    m_BorderPen.setWidth(2);
    m_BorderPen.setColor(Qt::blue);
    m_BorderPen.setCapStyle(Qt::SquareCap);
    m_BorderPen.setStyle(Qt::SolidLine);
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
    painter->setPen(m_BorderPen);

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
    m_BorderPen.setColor(Qt::blue);
    this->update(0, 0, m_Width, m_Height);
}

void BlockRemoveButton::hoverEnterEvent(QGraphicsSceneHoverEvent *)
{
    m_BorderPen.setColor(Qt::green);
    this->update(0, 0, m_Width, m_Height);
}

