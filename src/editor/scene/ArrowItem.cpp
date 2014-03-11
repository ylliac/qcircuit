/* 
 * File:   ArrowItem.cpp
 * Author: acailly
 * 
 * Created on 10 mars 2014, 18:34
 */

#include "ArrowItem.h"

#include <QtGui/QPainter>
#include <QtGui/QPainterPath>
#include <cmath>

const qreal Pi = 3.14;

ArrowItem::ArrowItem(BlockItem* startItem, BlockItem* endItem, QGraphicsItem* parent, QGraphicsScene* scene) :
QGraphicsLineItem(parent, scene)
{
    m_StartItem = startItem;
    m_EndItem = endItem;
    m_Color = Qt::green;

    setPen(QPen(m_Color, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    setFlag(QGraphicsItem::ItemIsSelectable, true);
}

ArrowItem::~ArrowItem()
{
}

QRectF ArrowItem::boundingRect() const
{
    qreal extra = (pen().width() + 20) / 2.0;

    return QRectF(line().p1(), QSizeF(line().p2().x() - line().p1().x(),
            line().p2().y() - line().p1().y()))
            .normalized()
            .adjusted(-extra, -extra, extra, extra);
}

QPainterPath ArrowItem::shape() const
{
    QPainterPath path = QGraphicsLineItem::shape();
    path.addPolygon(m_ArrowHead);
    return path;
}

void ArrowItem::updatePosition()
{
    QLineF line(mapFromItem(m_StartItem, 0, 0), mapFromItem(m_EndItem, 0, 0));
    setLine(line);
}

void ArrowItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *,
        QWidget *)
{
    if (m_StartItem->collidesWithItem(m_EndItem))
    {
        return;
    }

    QPen myPen = pen();
    myPen.setColor(m_Color);
    qreal arrowSize = 20;
    painter->setPen(myPen);
    painter->setBrush(m_Color);

    QLineF centerLine(m_StartItem->pos(), m_EndItem->pos());
    
    QPainterPath endPainterPath = m_EndItem->shape();
    QPointF p1 = endPainterPath.elementAt(0) + m_EndItem->pos();
    QPointF p2;
    QPointF intersectPoint;
    QLineF polyLine;
    for (int i = 1; i < endPainterPath.elementCount(); ++i)
    {
        p2 = endPainterPath.elementAt(i) + m_EndItem->pos();
        polyLine = QLineF(p1, p2);
        QLineF::IntersectType intersectType =
                polyLine.intersect(centerLine, &intersectPoint);
        if (intersectType == QLineF::BoundedIntersection)
        {
            break;
        }
        p1 = p2;
    }

    setLine(QLineF(intersectPoint, m_StartItem->pos()));

    double angle = acos(line().dx() / line().length());
    if (line().dy() >= 0)
    {
        angle = (Pi * 2) - angle;
    }

    QPointF arrowP1 = line().p1() + QPointF(sin(angle + Pi / 3) * arrowSize, cos(angle + Pi / 3) * arrowSize);
    QPointF arrowP2 = line().p1() + QPointF(sin(angle + Pi - Pi / 3) * arrowSize, cos(angle + Pi - Pi / 3) * arrowSize);

    m_ArrowHead.clear();
    m_ArrowHead << line().p1() << arrowP1 << arrowP2;
    painter->drawLine(line());
    painter->drawPolygon(m_ArrowHead);
    if (isSelected())
    {
        painter->setPen(QPen(m_Color, 1, Qt::DashLine));
        QLineF myLine = line();
        myLine.translate(0, 4.0);
        painter->drawLine(myLine);
        myLine.translate(0, -8.0);
        painter->drawLine(myLine);
    }
}

void ArrowItem::setColor(const QColor &color)
{
    m_Color = color;
}

