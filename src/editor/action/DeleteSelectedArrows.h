/* 
 * File:   DeleteSelectedArrows.h
 * Author: HOME
 *
 * Created on 14 juin 2014, 12:06
 */

#ifndef DELETESELECTEDARROWS_H
#define	DELETESELECTEDARROWS_H

#include "FBPEditorAction.h"

#include <QtGui/QGraphicsScene>

class DeleteSelectedArrows : public FBPEditorAction {
    Q_OBJECT
    
public:
    DeleteSelectedArrows(FBPEditor* editor);
    virtual ~DeleteSelectedArrows();
    
public slots:
    virtual void execute(QString arg1 = 0, QString arg2 = 0, QString arg3 = 0, QString arg4 = 0, QString arg5 = 0);
};

#endif	/* DELETESELECTEDARROWS_H */

