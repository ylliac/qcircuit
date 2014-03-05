/* 
 * File:   CreateNewBlock.h
 * Author: acailly
 *
 * Created on 5 mars 2014, 15:51
 */

#ifndef CREATENEWBLOCK_H
#define	CREATENEWBLOCK_H

#include "FBPEditorAction.h"

class CreateNewBlock : public FBPEditorAction {
    Q_OBJECT
    
public:
    CreateNewBlock(FBPEditor* parent);
    virtual ~CreateNewBlock();
    
public slots:
    virtual void execute();

};

#endif	/* CREATENEWBLOCK_H */

