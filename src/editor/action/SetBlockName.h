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
    SetBlockName(FBPEditor* editor);
    virtual ~SetBlockName();
    
public slots:
    virtual void execute(QString arg1 = 0, QString arg2 = 0, QString arg3 = 0, QString arg4 = 0, QString arg5 = 0);

};

#endif	/* SETBLOCKNAME_H */

