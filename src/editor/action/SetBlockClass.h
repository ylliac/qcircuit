/* 
 * File:   SetBlockClass.h
 * Author: HOME
 *
 * Created on 20 juillet 2014, 19:58
 */

#ifndef SETBLOCKCLASS_H
#define	SETBLOCKCLASS_H

#include "FBPEditorAction.h"

class SetBlockClass : public FBPEditorAction {
    Q_OBJECT
    
public:
    SetBlockClass(FBPEditor* editor);
    virtual ~SetBlockClass();
    
public slots:
    virtual void execute(QString arg1 = 0, QString arg2 = 0, QString arg3 = 0, QString arg4 = 0, QString arg5 = 0);

};

#endif	/* SETBLOCKCLASS_H */

