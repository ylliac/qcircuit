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
    FBPEditorAction(FBPEditor* parent);
    virtual ~FBPEditorAction();
    
    FBPEditor* getEditor() const;
    
public slots:
    virtual void execute() = 0;
    
private:
    FBPEditor* m_Editor;
};

#endif	/* FBPEDITORACTION_H */

