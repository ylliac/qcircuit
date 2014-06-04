/* 
 * File:   Debug.h
 * Author: acailly
 *
 * Created on 4 juin 2014, 17:20
 */

#ifndef DEBUG_H
#define	DEBUG_H

#include "FBPEditorAction.h"

class Debug : public FBPEditorAction {
    Q_OBJECT
    
public:
    Debug(FBPEditor* editor);
    virtual ~Debug();
    
public slots:
    virtual void execute(QString arg1 = 0, QString arg2 = 0, QString arg3 = 0, QString arg4 = 0, QString arg5 = 0);

};

#endif	/* DEBUG_H */

