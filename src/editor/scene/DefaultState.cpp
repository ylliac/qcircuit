/* 
 * File:   DefaultState.cpp
 * Author: acailly
 * 
 * Created on 5 mars 2014, 18:14
 */

#include "DefaultState.h"

#include <QtCore/QEvent>
#include <QtGui/QMouseEvent>
#include <QtGui/QGraphicsView>
#include <QtGui/QGraphicsScene>
#include <QtGui/QGraphicsSceneMouseEvent>

DefaultState::DefaultState(QObject* parent) :
QObject(parent)
{
}

DefaultState::~DefaultState()
{
}

bool DefaultState::eventFilter(QObject* obj, QEvent* event)
{
    if (event->type() == QEvent::GraphicsSceneMousePress)
    {
        QGraphicsSceneMouseEvent * mouseEvent = ((QGraphicsSceneMouseEvent *) event);
        if (mouseEvent->button() == Qt::LeftButton)
        {
            QGraphicsScene* scene = qobject_cast<QGraphicsScene*>(obj);
            if (scene != NULL)
            {
                m_Arrow = new QGraphicsLineItem(QLineF(mouseEvent->scenePos(), mouseEvent->scenePos()));
                m_Arrow->setPen(QPen(Qt::black, 2));
                scene->addItem(m_Arrow);
                return true;
            }
        }
    }
    if (event->type() == QEvent::GraphicsSceneMouseMove)
    {
        QGraphicsSceneMouseEvent * mouseEvent = ((QGraphicsSceneMouseEvent *) event);
        if (mouseEvent->button() == Qt::LeftButton && m_Arrow != NULL)
        {
            QLineF newLine(m_Arrow->line().p1(), mouseEvent->scenePos());
            m_Arrow->setLine(newLine);
            return true;
        }
    }
    if (event->type() == QEvent::GraphicsSceneMouseRelease)
    {
        QGraphicsSceneMouseEvent * mouseEvent = ((QGraphicsSceneMouseEvent *) event);
        if (mouseEvent->button() == Qt::LeftButton && m_Arrow != NULL)
        {
            QGraphicsScene* scene = qobject_cast<QGraphicsScene*>(obj);
            if (scene != NULL)
            {
                QList<QGraphicsItem *> startItems = scene->items(m_Arrow->line().p1());
                if (startItems.count() && startItems.first() == m_Arrow)
                {
                    startItems.removeFirst();
                }
                QList<QGraphicsItem *> endItems = scene->items(m_Arrow->line().p2());
                if (endItems.count() && endItems.first() == m_Arrow)
                {
                    endItems.removeFirst();
                }

                scene->removeItem(m_Arrow);
                delete m_Arrow;

                //        if (startItems.count() > 0 && endItems.count() > 0 &&
                //                startItems.first()->type() == DiagramItem::Type &&
                //                endItems.first()->type() == DiagramItem::Type &&
                //                startItems.first() != endItems.first())
                //        {
                //            DiagramItem *startItem =
                //                    qgraphicsitem_cast<DiagramItem *>(startItems.first());
                //            DiagramItem *endItem =
                //                    qgraphicsitem_cast<DiagramItem *>(endItems.first());
                //            Arrow *arrow = new Arrow(startItem, endItem);
                //            arrow->setColor(myLineColor);
                //            startItem->addArrow(arrow);
                //            endItem->addArrow(arrow);
                //            arrow->setZValue(-1000.0);
                //            addItem(arrow);
                //            arrow->updatePosition();
                //        }

                return true;
            }
        }
        m_Arrow = NULL;
    }

    return QObject::eventFilter(obj, event);
}

