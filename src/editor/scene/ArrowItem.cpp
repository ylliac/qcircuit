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
    myPen.setWidth(3);
    painter->setPen(myPen);
    painter->setBrush(m_Color);
    
    //------------------------------------------------------------------
    // ARROW BODY 
    //------------------------------------------------------------------
    QPointF startCenter = m_StartItem->pos() + m_StartItem->boundingRect().center();
    QPointF endCenter = m_EndItem->pos() + m_EndItem->boundingRect().center();

    QLineF centerLine(startCenter, endCenter);
    
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

    setLine(QLineF(startCenter, intersectPoint));
    painter->drawLine(line());
    
    //TODO ACY SUPPRIMER
    //------------------------------------------------------------------
    // ARROW HEAD 
    //------------------------------------------------------------------    
//    qreal arrowSize = 10;
//    double angle = acos(line().dx() / line().length());
//    if (line().dy() >= 0)
//    {
//        angle = (Pi * 2) - angle;
//    }
//
//    QPointF arrowP1 = line().p2() - QPointF(sin(angle + Pi / 3) * arrowSize, cos(angle + Pi / 3) * arrowSize);
//    QPointF arrowP2 = line().p2() - QPointF(sin(angle + Pi - Pi / 3) * arrowSize, cos(angle + Pi - Pi / 3) * arrowSize);
//
//    m_ArrowHead.clear();
//    m_ArrowHead << line().p2() << arrowP1 << arrowP2;
//    painter->drawPolygon(m_ArrowHead);   
        
    //------------------------------------------------------------------
    // ARROW BORDER 
    //------------------------------------------------------------------
    double angle = acos(line().dx() / line().length());
    if (line().dy() >= 0)
    {
        angle = (Pi * 2) - angle;
    }
    double dx = sin(angle + Pi / 4) * 3.0;
    double dy = cos(angle + Pi / 4) * 3.0;    
    
    painter->setPen(QPen(Qt::gray, 1, Qt::SolidLine));
    QLineF myLine = line();
    myLine.translate(dx, dy);
    painter->drawLine(myLine);
    myLine.translate(-2*dx, -2*dy);
    painter->drawLine(myLine); 
    
    //------------------------------------------------------------------
    // SELECTION 
    //------------------------------------------------------------------
    if (isSelected())
    {
        painter->setPen(QPen(Qt::black, 1, Qt::SolidLine));
        QLineF myLine = line();
        myLine.translate(dx, dy);
        painter->drawLine(myLine);
        myLine.translate(-2*dx, -2*dy);
        painter->drawLine(myLine);
    }
}

void ArrowItem::setColor(const QColor &color)
{
    m_Color = color;
}

