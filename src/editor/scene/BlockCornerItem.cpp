/* 
 * File:   BlockCornerItem.cpp
 * Author: acailly
 * 
 * Created on 5 mars 2014, 16:43
 */

#include "BlockCornerItem.h"

#include <QtGui/QPainter>

BlockCornerItem::BlockCornerItem(QGraphicsItem *parent, int corner) :
m_OutterborderColor(Qt::black),
m_OutterborderPen(),
m_Width(6),
m_Height(6),
m_MouseButtonState(kMouseReleased),
m_Corner(corner),
m_MouseDownX(0),
m_MouseDownY(0)
{
    setParentItem(parent);

    m_OutterborderPen.setWidth(2);
    m_OutterborderPen.setColor(m_OutterborderColor);

    setAcceptHoverEvents(true);
}

BlockCornerItem::~BlockCornerItem()
{
}

QRectF BlockCornerItem::boundingRect() const
{
    return QRectF(0, 0, m_Width, m_Height);
}

void BlockCornerItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    // fill the box with solid color, use sharp corners

    m_OutterborderPen.setCapStyle(Qt::SquareCap);
    m_OutterborderPen.setStyle(Qt::SolidLine);
    painter->setPen(m_OutterborderPen);

    QPointF topLeft(0, 0);
    QPointF bottomRight(m_Width, m_Height);

    QRectF rect(topLeft, bottomRight);

    QBrush brush(Qt::SolidPattern);
    brush.setColor(m_OutterborderColor);
    painter->fillRect(rect, brush);
}

void BlockCornerItem::setMouseState(int s)
{
    m_MouseButtonState = s;
}

int BlockCornerItem::getMouseState()
{
    return m_MouseButtonState;
}

int BlockCornerItem::getCorner()
{
    return m_Corner;
}

qreal BlockCornerItem::getMouseDownX()
{
    return m_MouseDownX;
}

void BlockCornerItem::setMouseDownX(qreal value)
{
    m_MouseDownX = value;
}

qreal BlockCornerItem::getMouseDownY()
{
    return m_MouseDownY;
}

void BlockCornerItem::setMouseDownY(qreal value)
{
    m_MouseDownY = value;
}

void BlockCornerItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *)
{
    m_OutterborderColor = Qt::black;
    this->update(0, 0, m_Width, m_Height);
}

void BlockCornerItem::hoverEnterEvent(QGraphicsSceneHoverEvent *)
{
    m_OutterborderColor = Qt::red;
    this->update(0, 0, m_Width, m_Height);
}

