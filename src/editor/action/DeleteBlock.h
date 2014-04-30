/* 
 * File:   DeleteBlock.h
 * Author: acailly
 *
 * Created on 30 avril 2014, 11:22
 */

#ifndef DELETEBLOCK_H
#define	DELETEBLOCK_H

#include "FBPEditorAction.h"

class BlockItem;

class DeleteBlock : public FBPEditorAction {
    Q_OBJECT
    
public:
    DeleteBlock(BlockItem* block);
    virtual ~DeleteBlock();
    
public slots:
    virtual void execute();
    
private:
    BlockItem* m_Block;

};

#endif	/* DELETEBLOCK_H */

