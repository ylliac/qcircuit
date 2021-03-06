/* 
 * File:   ArrowItem.cpp
 * Author: acailly
 * 
 * Created on 10 mars 2014, 18:34
 */

#include "ArrowItem.h"

#include <QtCore/qnumeric.h>
#include <QtGui/QPainter>
#include <QtGui/QPainterPath>
#include <QtGui/QTextBlockFormat>
#include <QtGui/QTextCursor>
#include <cmath>
#include <iostream>

const qreal Pi = 3.14;

ArrowItem::ArrowItem(BlockItem* startItem, BlockItem* endItem, QGraphicsItem* parent, QGraphicsScene* scene) :
QGraphicsLineItem(parent, scene)
{
    m_StartItem = startItem;
    m_EndItem = endItem;
    m_Color = Qt::green;

    setPen(QPen(m_Color, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    
    bool check = connect(startItem, SIGNAL(posChanged(BlockItem*)),this, SLOT(updateTextPosition()));
    Q_ASSERT(check);
    check = connect(endItem, SIGNAL(posChanged(BlockItem*)),this, SLOT(updateTextPosition()));
    Q_ASSERT(check);
    
    m_InputPortName = new QGraphicsTextItem(this);
    m_InputPortName->setPlainText("IN");
    
    m_OutputPortName = new QGraphicsTextItem(this);
    m_OutputPortName->setPlainText("OUT");
}

ArrowItem::~ArrowItem()
{
}

QString ArrowItem::getOutputPortName()
{
    return m_OutputPortName->toPlainText();
}
    
void ArrowItem::setOutputPortName(QString name)
{
    m_OutputPortName->setPlainText(name);
}

QString ArrowItem::getInputPortName()
{
    return m_InputPortName->toPlainText();
}

void ArrowItem::setInputPortName(QString name)
{
    m_InputPortName->setPlainText(name);
}

QRectF ArrowItem::boundingRect() const
{
    qreal extra = (pen().width() + 40) / 2.0;

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

BlockItem* ArrowItem::getStartBlock()
{
    return m_StartItem;
}
    
BlockItem* ArrowItem::getEndBlock()
{
    return m_EndItem;
}

void ArrowItem::updateTextPosition()
{        
    QLineF unitVector = line().unitVector();    
    if(!qIsNaN(unitVector.dx()))
    {            
        m_OutputPortName->setPos(
            line().p1().x() 
            - m_OutputPortName->boundingRect().width() / 2. 
            + m_OutputPortName->boundingRect().width() * unitVector.dx()
                , line().p1().y() 
                - m_OutputPortName->boundingRect().height() / 2. 
                + m_OutputPortName->boundingRect().height() * unitVector.dy()
        );

        m_InputPortName->setPos(
            line().p2().x() 
            - m_InputPortName->boundingRect().width() / 2. 
            - m_InputPortName->boundingRect().width() * unitVector.dx(),
                line().p2().y() 
                - m_InputPortName->boundingRect().height() / 2. 
                - m_InputPortName->boundingRect().height() * unitVector.dy());
    }
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
    
    //Intersection with start element
    QPainterPath startPainterPath = m_StartItem->shape();
    QPointF p1 = startPainterPath.elementAt(0) + m_StartItem->pos();
    QPointF p2;
    QPointF startIntersectPoint;
    QLineF polyLine;
    for (int i = 1; i < startPainterPath.elementCount(); ++i)
    {
        p2 = startPainterPath.elementAt(i) + m_StartItem->pos();
        polyLine = QLineF(p1, p2);
        QLineF::IntersectType intersectType =
                polyLine.intersect(centerLine, &startIntersectPoint);
        if (intersectType == QLineF::BoundedIntersection)
        {
            break;
        }
        p1 = p2;
    }
    
    //Intersection with end element
    QPainterPath endPainterPath = m_EndItem->shape();
    p1 = endPainterPath.elementAt(0) + m_EndItem->pos();
    QPointF endIntersectPoint;
    for (int i = 1; i < endPainterPath.elementCount(); ++i)
    {
        p2 = endPainterPath.elementAt(i) + m_EndItem->pos();
        polyLine = QLineF(p1, p2);
        QLineF::IntersectType intersectType =
                polyLine.intersect(centerLine, &endIntersectPoint);
        if (intersectType == QLineF::BoundedIntersection)
        {
            break;
        }
        p1 = p2;
    }

    setLine(QLineF(startIntersectPoint, endIntersectPoint));
    painter->drawLine(line());
        
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
    
    //DEBUG: Draw arrow bounding rect
    //    painter->setPen(Qt::red);
    //    painter->setBrush(Qt::NoBrush);
    //    painter->drawRect(boundingRect());
    
    //------------------------------------------------------------------
    // SELECTION 
    //------------------------------------------------------------------
    if (isSelected())
    {
        dx = sin(angle + Pi / 4) * 4.0;
        dy = cos(angle + Pi / 4) * 4.0;
        
        painter->setPen(QPen(QColor(124,181,242), 2, Qt::SolidLine)); //blue
        QLineF myLine = line();
        myLine.translate(dx, dy);
        painter->drawLine(myLine);
        myLine.translate(-2*dx, -2*dy);
        painter->drawLine(myLine);
    }
    
    updateTextPosition();
}

void ArrowItem::setColor(const QColor &color)
{
    m_Color = color;
}

