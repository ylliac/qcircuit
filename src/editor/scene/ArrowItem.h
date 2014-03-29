/* 
 * File:   ArrowItem.h
 * Author: acailly
 *
 * Created on 10 mars 2014, 18:34
 */

#ifndef ARROWITEM_H
#define	ARROWITEM_H

#include <QtGui/QGraphicsLineItem>
#include <QtGui/QPolygonF>
#include <QtGui/QColor>

#include "BlockItem.h"

class ArrowItem : public QObject, public QGraphicsLineItem{
    Q_OBJECT
    
public:
    ArrowItem(BlockItem* startItem, BlockItem* endItem, QGraphicsItem* parent = 0, QGraphicsScene* scene = 0);
    virtual ~ArrowItem();
    
    QRectF boundingRect() const;
    QPainterPath shape() const;
    
    void setColor(const QColor &color);    

public slots:
    void updateTextPosition();
    
protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget = 0);
    
private:
    BlockItem* m_StartItem;
    BlockItem* m_EndItem;
    QColor m_Color;
    QPolygonF m_ArrowHead;
    
    QGraphicsTextItem* m_InputPortName;
    QGraphicsTextItem* m_OutputPortName;

};

#endif	/* ARROWITEM_H */

