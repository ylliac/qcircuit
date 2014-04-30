/* 
 * File:   DeleteSelectedBlocks.h
 * Author: acailly
 *
 * Created on 30 avril 2014, 11:20
 */

#ifndef DELETESELECTEDBLOCKS_H
#define	DELETESELECTEDBLOCKS_H

#include "FBPEditorAction.h"

#include <QtGui/QGraphicsScene>

class DeleteSelectedBlocks : public FBPEditorAction {
    Q_OBJECT
    
public:
    DeleteSelectedBlocks(QGraphicsScene* scene);
    virtual ~DeleteSelectedBlocks();
    
public slots:
    virtual void execute();
    
private:
    QGraphicsScene* m_Scene;

};

#endif	/* DELETESELECTEDBLOCKS_H */

