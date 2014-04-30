/* 
 * File:   BlockItem.h
 * Author: acailly
 *
 * Created on 5 mars 2014, 16:15
 */

#ifndef BLOCKITEM_H
#define	BLOCKITEM_H

#include <QtGui/QGraphicsItem>
#include <QtGui/QColor>
#include <QtGui/QPen>

class BlockCornerItem;
class BlockRemoveButton;
class BlockConnectButton;
class FBPEditor;

class BlockItem : public QObject, public QGraphicsItem {
    Q_OBJECT
    
public:
    BlockItem(FBPEditor* editor);
    virtual ~BlockItem();

    virtual QRectF boundingRect() const;
    virtual QPainterPath shape() const;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    ///Handle hover event
    virtual void hoverEnterEvent(QGraphicsSceneHoverEvent * event);
    virtual void hoverLeaveEvent(QGraphicsSceneHoverEvent * event);

    virtual bool sceneEventFilter(QGraphicsItem * watched, QEvent * event);
    virtual QVariant itemChange(GraphicsItemChange change, const QVariant &value);

    virtual QString name();
    virtual void setName(QString name);
    
    FBPEditor* getEditor();
    
signals:
    void posChanged(BlockItem* item);
    
private:
    void updateChildItemsPositions();
    void incrementSize(int x, int y);

    ///Sample text to go in the title area.
    QGraphicsTextItem m_Text;
    ///The hover event handlers will toggle this between red and black
    QColor m_OutterborderColor;
    ///The the pen is used to paint the red/black border
    QPen m_OutterborderPen;

    ///Dimensions
    qreal m_Width;
    qreal m_Height;

    ///Dimensions allowed to the corner
    int m_XcornerGrabBuffer;
    int m_YcornerGrabBuffer;

    ///Real dimensions of the block (global dimensions - corner dimensions)
    qreal m_DrawingRight;
    qreal m_DrawingBottom;
    qreal m_DrawingLeft;
    qreal m_DrawingTop;

    /// 0,1,2,3  - starting at x=0,y=0 and moving clockwise around the box
    BlockCornerItem* m_Corners[4];
    
    //Remove button
    BlockRemoveButton* m_RemoveButton;
    
    //Connect button
    BlockConnectButton* m_ConnectButton;
    
    //Editor interface
    FBPEditor* m_Editor;
};

#endif	/* BLOCKITEM_H */

