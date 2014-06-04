/* 
 * File:   FBPEditorAction.h
 * Author: acailly
 *
 * Created on 3 mars 2014, 18:32
 */

#ifndef FBPEDITORACTION_H
#define	FBPEDITORACTION_H

#include <QtCore/QObject>

#include "editor/FBPEditor.h"

class FBPEditorAction : public QObject {
    Q_OBJECT
        
public:
    FBPEditorAction(FBPEditor* editor);
    virtual ~FBPEditorAction();
    
    FBPEditor* getEditor();
    
public slots:
    virtual void execute(QString arg1 = 0, QString arg2 = 0, QString arg3 = 0, QString arg4 = 0, QString arg5 = 0) = 0;
    
private:
    FBPEditor* m_Editor;
};

#endif	/* FBPEDITORACTION_H */

