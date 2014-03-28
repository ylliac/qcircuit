/* 
 * File:   BlockConnectButton.h
 * Author: acailly
 *
 * Created on 10 mars 2014, 17:24
 */

#ifndef BLOCKCONNECTBUTTON_H
#define	BLOCKCONNECTBUTTON_H

#include <QtGui/QGraphicsItem>
#include <QtGui/QPen>
#include <QtGui/QBrush>

class BlockConnectButton : public QGraphicsItem {
public:
    BlockConnectButton(QGraphicsItem *parent = 0);
    virtual ~BlockConnectButton();
    
    virtual QRectF boundingRect() const;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    ///Mouse hover events
    virtual void hoverEnterEvent(QGraphicsSceneHoverEvent * event);
    virtual void hoverLeaveEvent(QGraphicsSceneHoverEvent * event);

    virtual bool sceneEventFilter(QGraphicsItem * watched, QEvent * event);
    
private:
    
    ///Dimensions
    qreal m_Width;
    qreal m_Height;
    
    ///Pen
    QPen m_Pen;
    ///Brush
    QBrush m_Brush;
    
    QGraphicsLineItem* m_Arrow;

};

#endif	/* BLOCKCONNECTBUTTON_H */

