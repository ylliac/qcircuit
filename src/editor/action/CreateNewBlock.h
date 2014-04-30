/* 
 * File:   CreateNewBlock.h
 * Author: acailly
 *
 * Created on 5 mars 2014, 15:51
 */

#ifndef CREATENEWBLOCK_H
#define	CREATENEWBLOCK_H

#include "FBPEditorAction.h"

#include <QtGui/QGraphicsScene>

class CreateNewBlock : public FBPEditorAction {
    Q_OBJECT
    
public:
    CreateNewBlock(FBPEditor* editor);
    virtual ~CreateNewBlock();
    
public slots:
    virtual void execute(QString arg1 = 0, QString arg2 = 0, QString arg3 = 0, QString arg4 = 0, QString arg5 = 0);

};

#endif	/* CREATENEWBLOCK_H */

