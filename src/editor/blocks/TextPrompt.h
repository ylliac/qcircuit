/* 
 * File:   TextPrompt.h
 * Author: acailly
 *
 * Created on 3 mars 2014, 15:21
 */

#ifndef TEXTPROMPT_H
#define	TEXTPROMPT_H

#include <QtCore/QVariant>
#include "editor/blocks/FBPEditorBlock.h"

class QInputDialog;

class TextPrompt : public FBPEditorBlock {
    Q_OBJECT
    
public:
    TextPrompt();
    virtual ~TextPrompt();
    
public slots:
    void inTrigger(QVariant v = QVariant(true));
    
signals:
    void outValue(QVariant v = QVariant(true));
    
protected:
    virtual void attachImpl();
    virtual void detachImpl();    
    
private:
    QInputDialog* m_Item;
};

#endif	/* TEXTPROMPT_H */

