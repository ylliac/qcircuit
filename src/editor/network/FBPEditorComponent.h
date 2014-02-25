/* 
 * File:   FBPEditorComponent.h
 * Author: acailly
 *
 * Created on 25 février 2014, 11:55
 */

#ifndef FBPEDITORCOMPONENT_H
#define	FBPEDITORCOMPONENT_H

#include "core/FBPComponent.h"
#include "editor/FBPEditor.h"

class FBPEditorComponent : public FBPComponent
{
    Q_OBJECT    
public:
    FBPEditorComponent();
    virtual ~FBPEditorComponent();

protected:
    void receiveEditor();
    FBPEditor* getEditor();
    
private:
    FBPEditor* m_Editor;
};

#endif	/* FBPEDITORCOMPONENT_H */

