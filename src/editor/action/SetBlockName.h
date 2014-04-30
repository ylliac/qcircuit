/* 
 * File:   SetBlockName.h
 * Author: acailly
 *
 * Created on 30 avril 2014, 11:34
 */

#ifndef SETBLOCKNAME_H
#define	SETBLOCKNAME_H

#include "FBPEditorAction.h"

class BlockItem;

class SetBlockName : public FBPEditorAction {
    Q_OBJECT
    
public:
    SetBlockName(BlockItem* block, QString name);
    virtual ~SetBlockName();
    
public slots:
    virtual void execute();
    
private:
    BlockItem* m_Block;
    QString m_Name;

};

#endif	/* SETBLOCKNAME_H */

