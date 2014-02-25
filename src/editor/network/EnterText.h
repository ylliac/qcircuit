/* 
 * File:   EnterText.h
 * Author: acailly
 *
 * Created on 25 février 2014, 12:25
 */

#ifndef ENTERTEXT_H
#define	ENTERTEXT_H

#include "editor/network/FBPEditorComponent.h"

class EnterText : public FBPEditorComponent
{
    Q_OBJECT
public:
    EnterText();
    virtual ~EnterText();
    
protected:
    virtual void execute();

private slots:
    void uiPrompt();
    
private:
    QString m_Text;
};

#endif	/* ENTERTEXT_H */

