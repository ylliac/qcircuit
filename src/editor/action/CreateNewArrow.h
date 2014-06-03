/* 
 * File:   CreateNewArrow.h
 * Author: acailly
 *
 * Created on 3 juin 2014, 19:02
 */

#ifndef CREATENEWARROW_H
#define	CREATENEWARROW_H

#include "FBPEditorAction.h"

#include <QtGui/QGraphicsScene>

class CreateNewArrow : public FBPEditorAction {
    Q_OBJECT
    
public:
    CreateNewArrow(FBPEditor* editor);
    virtual ~CreateNewArrow();
    
public slots:
    virtual void execute(QString arg1 = 0, QString arg2 = 0, QString arg3 = 0, QString arg4 = 0, QString arg5 = 0);

};

#endif	/* CREATENEWARROW_H */

