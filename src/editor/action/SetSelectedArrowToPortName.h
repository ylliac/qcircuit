/* 
 * File:   SetSelectedArrowToPortName.h
 * Author: HOME
 *
 * Created on 14 juin 2014, 11:56
 */

#ifndef SETSELECTEDARROWTOPORTNAME_H
#define	SETSELECTEDARROWTOPORTNAME_H

#include "FBPEditorAction.h"

class SetSelectedArrowToPortName : public FBPEditorAction {
    Q_OBJECT
    
public:
    SetSelectedArrowToPortName(FBPEditor* editor);
    virtual ~SetSelectedArrowToPortName();
    
public slots:
    virtual void execute(QString arg1 = 0, QString arg2 = 0, QString arg3 = 0, QString arg4 = 0, QString arg5 = 0);

};

#endif	/* SETSELECTEDARROWTOPORTNAME_H */

