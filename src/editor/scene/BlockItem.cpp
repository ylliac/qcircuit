/* 
 * File:   BlockItem.cpp
 * Author: acailly
 * 
 * Created on 5 mars 2014, 16:15
 */

#include "BlockItem.h"

#include <QtCore/QEvent>
#include <QtGui/QPainter>
#include <QtGui/QGraphicsSceneMouseEvent>

#include "BlockCornerItem.h"
#include "BlockRemoveButton.h"
#include "BlockConnectButton.h"

BlockItem::BlockItem() :
m_Text(),
m_OutterborderColor(Qt::black),
m_OutterborderPen(),
m_Width(150),
m_Height(100),
m_XcornerGrabBuffer(20),
m_YcornerGrabBuffer(20),
m_DrawingRight(m_Width - m_XcornerGrabBuffer),
m_DrawingBottom(m_Height - m_YcornerGrabBuffer),
m_DrawingLeft(m_XcornerGrabBuffer),
m_DrawingTop(m_YcornerGrabBuffer),
m_RemoveButton(NULL),
m_ConnectButton(NULL) {
    m_OutterborderPen.setWidth(2);
    m_OutterborderPen.setColor(m_OutterborderColor);

    m_Text.setPos(35, 35);
    m_Text.setPlainText("text goes here");
    m_Text.setParentItem(this);
//    m_Text.setFont(QFont("Calibri", 10, QFont::Bold));
    
    setAcceptHoverEvents(true);
    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemIsSelectable);
}

BlockItem::~BlockItem() {
}

QRectF BlockItem::boundingRect() const {
    return QRectF(m_DrawingLeft, m_DrawingTop, m_DrawingRight - m_DrawingLeft, m_DrawingBottom - m_DrawingTop);
}

void BlockItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) {
    //    //------------------------------------------------------------------
    //    // DROP SHADOW 
    //    //------------------------------------------------------------------
    //    
    //    /*
    //     The drop shadow effect will be created by drawing a filled, rounded corner rectangle with a gradient fill.
    //     Then on top of this will be drawn  filled, rounded corner rectangle, filled with a solid color, and offset such that the gradient filled
    //     box is only visible below for a few pixels on two edges.
    //
    //     The total box size is _width by _height. So the top box will start at (0,0) and go to (_width-shadowThickness, _height-shadowThickness),
    //     while the under box will be offset, and start at (shadowThickness+0, shadowThickness+0) and go to  (_width, _height).
    //     */
    //    
    //    int shadowThickness = 3;
    //
    //    QLinearGradient gradient;
    //    gradient.setStart(m_DrawingLeft, m_DrawingTop);
    //    gradient.setFinalStop(m_DrawingRight, m_DrawingTop);
    //    // starting color of the gradient - can play with the starting color and ,point since its not visible anyway
    //    QColor grey1(150, 150, 150, 125); 
    //    // grey2 is ending color of the gradient - this is what will show up as the shadow. the last parameter is the alpha blend, its set
    //    // to 125 allowing a mix of th color and and the background, making more realistic shadow effect.
    //    QColor grey2(225, 225, 225, 125);
    //    gradient.setColorAt((qreal) 0, grey1);
    //    gradient.setColorAt((qreal) 1, grey2);
    //    QBrush brush(gradient);
    //    painter->setBrush(brush);
    //
    //    // for the desired effect, no border will be drawn, and because a brush was set, the drawRoundRect will fill the box with the gradient brush.
    //    m_OutterborderPen.setStyle(Qt::NoPen);
    //    painter->setPen(m_OutterborderPen);
    //
    //    QPointF topLeft(m_DrawingLeft, m_DrawingLeft);
    //    QPointF bottomRight(m_DrawingRight, m_DrawingBottom);
    //
    //    QRectF rect(topLeft, bottomRight);
    //
    //    painter->drawRoundRect(rect, 25, 25); // corner radius of 25 pixels
    //
    //    //------------------------------------------------------------------
    //    // CONTENT 
    //    //------------------------------------------------------------------
    //    
    //    // draw the top box, the visible one
    //    QBrush contentBrush(QColor(243, 255, 216, 255), Qt::SolidPattern);
    //    painter->setBrush(contentBrush);
    //
    //    QPointF topLeft2(m_DrawingLeft, m_DrawingTop);
    //    QPointF bottomRight2(m_DrawingRight - shadowThickness, m_DrawingBottom - shadowThickness);
    //
    //    QRectF rect2(topLeft2, bottomRight2);
    //
    //    painter->drawRoundRect(rect2, 25, 25);

    QLinearGradient gradient;
    gradient.setStart(m_DrawingLeft, m_DrawingBottom);
    gradient.setFinalStop(m_DrawingLeft, m_DrawingTop);
    QColor start(73, 132, 180, 255);
    QColor end(97, 155, 203, 255);
    gradient.setColorAt((qreal) 0, start);
    gradient.setColorAt((qreal) 1, end);
    QBrush brush(gradient);
    painter->setBrush(brush);

    QPointF topLeft(m_DrawingLeft, m_DrawingTop);
    QPointF bottomRight(m_DrawingRight, m_DrawingBottom);

    QRectF rect(topLeft, bottomRight);
    painter->drawRect(rect);

    //------------------------------------------------------------------
    // SELECTION BORDER 
    //------------------------------------------------------------------
    if (isSelected()) {
        painter->setBrush(Qt::NoBrush);
        QPen selectionPen(QColor(255, 0, 0, 255));
        selectionPen.setWidth(3);
        painter->setPen(selectionPen);
        painter->drawRect(rect);
    }
}

void BlockItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *) {
    m_OutterborderColor = Qt::black;

    m_Corners[0]->setParentItem(NULL);
    m_Corners[1]->setParentItem(NULL);
    m_Corners[2]->setParentItem(NULL);
    m_Corners[3]->setParentItem(NULL);

    delete m_Corners[0];
    delete m_Corners[1];
    delete m_Corners[2];
    delete m_Corners[3];

    m_RemoveButton->setParentItem(NULL);
    delete m_RemoveButton;

    m_ConnectButton->setParentItem(NULL);
    delete m_ConnectButton;
}

void BlockItem::hoverEnterEvent(QGraphicsSceneHoverEvent *) {
    m_OutterborderColor = Qt::red;

    m_Corners[0] = new BlockCornerItem(this, 0);
    m_Corners[1] = new BlockCornerItem(this, 1);
    m_Corners[2] = new BlockCornerItem(this, 2);
    m_Corners[3] = new BlockCornerItem(this, 3);

    m_Corners[0]->installSceneEventFilter(this);
    m_Corners[1]->installSceneEventFilter(this);
    m_Corners[2]->installSceneEventFilter(this);
    m_Corners[3]->installSceneEventFilter(this);

    m_RemoveButton = new BlockRemoveButton(this);
    m_ConnectButton = new BlockConnectButton(this);

    updateChildItemsPositions();
}

void BlockItem::updateChildItemsPositions() {
    m_Corners[0]->setPos(m_DrawingLeft, m_DrawingTop);
    m_Corners[1]->setPos(m_DrawingRight, m_DrawingTop);
    m_Corners[2]->setPos(m_DrawingRight, m_DrawingBottom);
    m_Corners[3]->setPos(m_DrawingLeft, m_DrawingBottom);

    m_RemoveButton->setPos(m_DrawingLeft - m_RemoveButton->boundingRect().width() / 2.0, m_DrawingTop - m_RemoveButton->boundingRect().height() / 2.0);
    m_ConnectButton->setPos(m_DrawingRight - m_RemoveButton->boundingRect().width() / 2.0, m_DrawingBottom / 2.0);
}

void BlockItem::incrementSize(int x, int y) {
    m_Width += x;
    m_Height += y;

    m_DrawingRight = m_Width - m_XcornerGrabBuffer;
    m_DrawingBottom = m_Height - m_YcornerGrabBuffer;
}

bool BlockItem::sceneEventFilter(QGraphicsItem * watched, QEvent * event) {
    BlockCornerItem * corner = dynamic_cast<BlockCornerItem *> (watched);
    if (corner == NULL) {
        // not expected to get here
        return false;
    }

    QGraphicsSceneMouseEvent * mevent = dynamic_cast<QGraphicsSceneMouseEvent*> (event);
    if (mevent == NULL) {
        // this is not one of the mouse events we are interrested in
        return false;
    }

    switch (event->type()) {
            // if the mouse went down, record the x,y coords of the press, record it inside the corner object
        case QEvent::GraphicsSceneMousePress:
        {
            corner->setMouseState(BlockCornerItem::kMouseDown);
            corner->setMouseDownX(mevent->pos().x());
            corner->setMouseDownY(mevent->pos().y());
        }
            break;

        case QEvent::GraphicsSceneMouseRelease:
        {
            corner->setMouseState(BlockCornerItem::kMouseReleased);
        }
            break;

        case QEvent::GraphicsSceneMouseMove:
        {
            corner->setMouseState(BlockCornerItem::kMouseMoving);
        }
            break;

        default:
            // we dont care about the rest of the events
            return false;
            break;
    }

    if (corner->getMouseState() == BlockCornerItem::kMouseMoving) {

        qreal x = mevent->pos().x(), y = mevent->pos().y();

        // depending on which corner has been grabbed, we want to move the position
        // of the item as it grows/shrinks accordingly. so we need to eitehr add
        // or subtract the offsets based on which corner this is.

        int XaxisSign = 0;
        int YaxisSign = 0;
        switch (corner->getCorner()) {
            case 0:
            {
                XaxisSign = +1;
                YaxisSign = +1;
            }
                break;

            case 1:
            {
                XaxisSign = -1;
                YaxisSign = +1;
            }
                break;

            case 2:
            {
                XaxisSign = -1;
                YaxisSign = -1;
            }
                break;

            case 3:
            {
                XaxisSign = +1;
                YaxisSign = -1;
            }
                break;

        }

        // if the mouse is being dragged, calculate a new size and also re-position
        // the box to give the appearance of dragging the corner out/in to resize the box

        int xMoved = corner->getMouseDownX() - x;
        int yMoved = corner->getMouseDownY() - y;

        int newWidth = m_Width + (XaxisSign * xMoved);
        if (newWidth < 40) newWidth = 40;

        int newHeight = m_Height + (YaxisSign * yMoved);
        if (newHeight < 40) newHeight = 40;

        int deltaWidth = newWidth - m_Width;
        int deltaHeight = newHeight - m_Height;

        incrementSize(deltaWidth, deltaHeight);

        deltaWidth *= (-1);
        deltaHeight *= (-1);

        if (corner->getCorner() == 0) {
            int newXpos = this->pos().x() + deltaWidth;
            int newYpos = this->pos().y() + deltaHeight;
            this->setPos(newXpos, newYpos);
        } else if (corner->getCorner() == 1) {
            int newYpos = this->pos().y() + deltaHeight;
            this->setPos(this->pos().x(), newYpos);
        } else if (corner->getCorner() == 3) {
            int newXpos = this->pos().x() + deltaWidth;
            this->setPos(newXpos, this->pos().y());
        }

        updateChildItemsPositions();

        update();
    }

    // true => do not send event to watched - we are finished with this event
    return true;
}

