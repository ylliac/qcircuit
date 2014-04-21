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
    static QList<ArrowItem*> getArrows(QGraphicsScene* scene);
    
    static QList<ArrowItem*> getConnectedArrows(QGraphicsScene* scene, BlockItem* block);

};

#endif	/* SCENEDETECTIVE_H */
