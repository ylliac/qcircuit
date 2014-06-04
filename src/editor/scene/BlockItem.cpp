/* 
 * File:   BlockItem.cpp
 * Author: acailly
 * 
 * Created on 5 mars 2014, 16:15
 */

#include "BlockItem.h"

#include <QtCore/QEvent>
#include <QtGui/QPainter>
#include <QtGui/QGraphicsScene>
#include <QtGui/QGraphicsSceneMouseEvent>

#include "BlockCornerItem.h"
#include "BlockRemoveButton.h"
#include "BlockConnectButton.h"

BlockItem::BlockItem(FBPEditor* editor) :
m_Text(),
m_OutterborderColor(Qt::gray),
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
m_ConnectButton(NULL),
m_Editor(editor)
{
    m_OutterborderPen.setWidth(2);
    m_OutterborderPen.setColor(m_OutterborderColor);

    m_Text.setPos(50, 35);
    m_Text.setParentItem(this);
    m_Text.setFont(QFont("Helvetica", 10, QFont::Bold));
    
    setAcceptHoverEvents(true);
    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemIsSelectable);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges);
    
    setName("Block");
}

BlockItem::~BlockItem() {
}

FBPEditor* BlockItem::getEditor()
{
    return m_Editor;
}

QRectF BlockItem::boundingRect() const {
    return QRectF(0, 0, m_Width, m_Height);
}

QPainterPath BlockItem::shape() const
{
    QPainterPath path;
    QRectF shape(m_DrawingLeft, m_DrawingTop, m_DrawingRight - m_DrawingLeft, m_DrawingBottom - m_DrawingTop);
    path.addRect(shape);
    return path;
}

QString BlockItem::name()
{
    return m_Text.toPlainText();
}

void BlockItem::setName(QString name)
{
    m_Text.setPlainText(name);
}

QVariant BlockItem::itemChange(GraphicsItemChange change, const QVariant &value)
 {
     if (change == ItemPositionChange && scene() != NULL) {         
         emit posChanged(this);
     }
     return QGraphicsItem::itemChange(change, value);
 }

void BlockItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) 
{   
    QLinearGradient gradient;
    gradient.setStart(m_DrawingLeft, m_DrawingBottom);
    gradient.setFinalStop(m_DrawingLeft, m_DrawingTop);
//    QColor start(127, 210, 251, 255); // blue
//    QColor start(245,245,245); //light gray
    QColor start(238,238,240); //gray
    QColor end = start;
    gradient.setColorAt((qreal) 0, start);
    gradient.setColorAt((qreal) 1, end);
    QBrush brush(gradient);
    painter->setBrush(brush);
    QPen pen;
    pen.setColor(m_OutterborderColor);
    pen.setWidth(2);
    painter->setPen(pen);

    QPointF topLeft(m_DrawingLeft, m_DrawingTop);
    QPointF bottomRight(m_DrawingRight, m_DrawingBottom);

    QRectF rect(topLeft, bottomRight);
    painter->drawRect(rect);

    //------------------------------------------------------------------
    // SELECTION 
    //------------------------------------------------------------------
    if (isSelected()) {
        QPointF selectionTopLeft(m_DrawingLeft-2, m_DrawingTop-2);
        QPointF selectionBottomRight(m_DrawingRight+2, m_DrawingBottom+2);
        QRectF selectionRect(selectionTopLeft, selectionBottomRight);
        painter->setBrush(Qt::NoBrush);
        QPen selectionPen;
        selectionPen.setColor(QColor(124,181,242)); //blue
        selectionPen.setWidth(2);
        selectionPen.setStyle(Qt::SolidLine);
        painter->setPen(selectionPen);
        painter->drawRect(selectionRect);
    }
}

void BlockItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *) {
//    m_OutterborderColor = QColor(80,80,80);
    m_OutterborderColor = Qt::gray;

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
    
    this->update(boundingRect());
}

void BlockItem::hoverEnterEvent(QGraphicsSceneHoverEvent *) {
    m_OutterborderColor = Qt::black;

    m_Corners[0] = new BlockCornerItem(this, 0);
    m_Corners[1] = new BlockCornerItem(this, 1);
    m_Corners[2] = new BlockCornerItem(this, 2);
    m_Corners[3] = new BlockCornerItem(this, 3);

    m_Corners[0]->installSceneEventFilter(this);
    m_Corners[1]->installSceneEventFilter(this);
    m_Corners[2]->installSceneEventFilter(this);
    m_Corners[3]->installSceneEventFilter(this);
    
    //TODO ACY
    m_Corners[0]->setVisible(false);
    m_Corners[1]->setVisible(false);
    m_Corners[2]->setVisible(false);
    m_Corners[3]->setVisible(false);

    m_RemoveButton = new BlockRemoveButton(this);
    m_ConnectButton = new BlockConnectButton(this);

    updateChildItemsPositions();
    
    this->update(boundingRect());
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

