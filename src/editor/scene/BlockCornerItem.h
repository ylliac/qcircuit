/* 
 * File:   BlockCornerItem.h
 * Author: acailly
 *
 * Created on 5 mars 2014, 16:43
 */

#ifndef BLOCKCORNERITEM_H
#define	BLOCKCORNERITEM_H

#include <QtGui/QGraphicsItem>
#include <QtGui/QColor>
#include <QtGui/QPen>

class BlockCornerItem : public QGraphicsItem {
public:
    BlockCornerItem(QGraphicsItem *parent = 0, int corner = 0);
    virtual ~BlockCornerItem();

    enum {
        kMouseReleased = 0, kMouseDown, kMouseMoving
    };

    virtual QRectF boundingRect() const;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    ///Mouse hover events
    virtual void hoverEnterEvent(QGraphicsSceneHoverEvent * event);
    virtual void hoverLeaveEvent(QGraphicsSceneHoverEvent * event);

    ///Corner    
    int getCorner();

    ///Mouse state
    int getMouseState();
    void setMouseState(int);

    ///Mouse last position
    qreal getMouseDownX();
    void setMouseDownX(qreal value);
    qreal getMouseDownY();
    void setMouseDownY(qreal value);

private:
    ///The hover event handlers will toggle this between red and black
    QColor m_OutterborderColor;
    ///The pen is used to paint the red/black border
    QPen m_OutterborderPen;
    ///Dimensions
    qreal m_Width;
    qreal m_Height;
    //Mouse state
    int m_MouseButtonState;
    ///Corner
    // 0,1,2,3  - starting at x=0,y=0 and moving clockwise around the box
    int m_Corner;
    //Mouse last position
    qreal m_MouseDownX;
    qreal m_MouseDownY;
};

#endif	/* BLOCKCORNERITEM_H */

