/* 
 * File:   CreateNewBlock.h
 * Author: acailly
 *
 * Created on 25 février 2014, 11:44
 */

#ifndef CREATENEWBLOCK_H
#define	CREATENEWBLOCK_H

#include "editor/network/FBPEditorComponent.h"

class CreateNewComponent : public FBPEditorComponent
{
    Q_OBJECT
public:
    CreateNewComponent();
    virtual ~CreateNewComponent();
        
protected:
    virtual void execute();
    
private slots:
    void uiCreateRect();
    
private:
    QString m_Name;    
};

#endif	/* CREATENEWBLOCK_H */

