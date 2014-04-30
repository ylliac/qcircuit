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
    CreateNewBlock(QGraphicsScene* scene);
    virtual ~CreateNewBlock();
    
public slots:
    virtual void execute();
    
private:
    QGraphicsScene* m_Scene;

};

#endif	/* CREATENEWBLOCK_H */

