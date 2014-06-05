/* 
 * File:   SceneDetective.h
 * Author: HOME
 *
 * Created on 21 avril 2014, 11:36
 */

#ifndef SCENEDETECTIVE_H
#define	SCENEDETECTIVE_H

#include <QtCore/QList>
#include <QtGui/QGraphicsScene>
#include "BlockItem.h"
#include "ArrowItem.h"


class SceneDetective {
public:
    virtual ~SceneDetective(){}

    static QList<BlockItem*> getBlocks(QGraphicsScene* scene);
    static BlockItem* getBlock(QString name, QGraphicsScene* scene);
    static QList<BlockItem*> getSelectedBlocks(QGraphicsScene* scene);
    
    static QList<ArrowItem*> getArrows(QGraphicsScene* scene);    
    static QList<ArrowItem*> getConnectedArrows(QGraphicsScene* scene, BlockItem* block);
    static QList<ArrowItem*> getSelectedArrows(QGraphicsScene* scene);
    
    static QString newUniqueNonEmptyBlockName(QGraphicsScene* scene, QString name);
};

#endif	/* SCENEDETECTIVE_H */

