/* 
 * File:   BlockRemoveButton.h
 * Author: acailly
 *
 * Created on 10 mars 2014, 11:10
 */

#ifndef BLOCKREMOVEBUTTON_H
#define	BLOCKREMOVEBUTTON_H

#include <QtGui/QGraphicsItem>
#include <QtGui/QPen>

class BlockRemoveButton : public QGraphicsItem {
public:
    BlockRemoveButton(QGraphicsItem *parent = 0);
    virtual ~BlockRemoveButton();
    
    virtual QRectF boundingRect() const;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    ///Mouse hover events
    virtual void hoverEnterEvent(QGraphicsSceneHoverEvent * event);
    virtual void hoverLeaveEvent(QGraphicsSceneHoverEvent * event);
    
private:
    
    ///Dimensions
    qreal m_Width;
    qreal m_Height;
    
    ///Border pen
    QPen m_BorderPen;

};

#endif	/* BLOCKREMOVEBUTTON_H */

