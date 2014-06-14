/* 
 * File:   SetSelectedArrowFromPortName.h
 * Author: HOME
 *
 * Created on 14 juin 2014, 11:41
 */

#ifndef SETSELECTEDARROWFROMPORTNAME_H
#define	SETSELECTEDARROWFROMPORTNAME_H

#include "FBPEditorAction.h"

class SetSelectedArrowFromPortName : public FBPEditorAction {
    Q_OBJECT
    
public:
    SetSelectedArrowFromPortName(FBPEditor* editor);
    virtual ~SetSelectedArrowFromPortName();
    
public slots:
    virtual void execute(QString arg1 = 0, QString arg2 = 0, QString arg3 = 0, QString arg4 = 0, QString arg5 = 0);

};

#endif	/* SETSELECTEDARROWFROMPORTNAME_H */

