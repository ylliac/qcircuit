/* 
 * File:   DeleteBlock.h
 * Author: acailly
 *
 * Created on 30 avril 2014, 11:22
 */

#ifndef DELETEBLOCK_H
#define	DELETEBLOCK_H

#include "FBPEditorAction.h"

class DeleteBlock : public FBPEditorAction {
    Q_OBJECT
    
public:
    DeleteBlock(FBPEditor* editor);
    virtual ~DeleteBlock();
    
public slots:
    virtual void execute(QString blockName = 0, QString arg2 = 0, QString arg3 = 0, QString arg4 = 0, QString arg5 = 0);
};

#endif	/* DELETEBLOCK_H */

