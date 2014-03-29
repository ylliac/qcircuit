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

    virtual bool sceneEventFilter(QGraphicsItem * watched, QEvent * event);
    
private:
    
    ///Dimensions
    qreal m_Width;
    qreal m_Height;
    
    ///Pen
    QPen m_Pen;
    ///Brush
    QBrush m_Brush;

};

#endif	/* BLOCKREMOVEBUTTON_H */

