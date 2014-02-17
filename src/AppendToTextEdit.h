/* 
 * File:   AppendToTextEdit.h
 * Author: acailly
 *
 * Created on 29 janvier 2014, 18:14
 */

#ifndef APPENDTOTEXTEDIT_H
#define	APPENDTOTEXTEDIT_H

#include "core/FBPComponent.h"

class QListWidget;

class AppendToTextEdit : public FBPComponent{
public:
    AppendToTextEdit(QListWidget* textEdit);
    virtual ~AppendToTextEdit();
    
protected:
    virtual void execute();
    
private:
    QListWidget* m_TextEdit;
};

#endif	/* APPENDTOTEXTEDIT_H */

