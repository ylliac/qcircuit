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
    DeleteSelectedBlocks(FBPEditor* editor);
    virtual ~DeleteSelectedBlocks();
    
public slots:
    virtual void execute(QString arg1 = 0, QString arg2 = 0, QString arg3 = 0, QString arg4 = 0, QString arg5 = 0);
};

#endif	/* DELETESELECTEDBLOCKS_H */

