/* 
 * File:   Button.h
 * Author: acailly
 *
 * Created on 25 février 2014, 11:11
 */

#ifndef BUTTON_H
#define	BUTTON_H

#include <QtCore/QVariant>
#include "editor/blocks/FBPEditorBlock.h"

class QGraphicsProxyWidget;

class Button : public FBPEditorBlock {
    Q_OBJECT
    
public:
    Button();
    virtual ~Button();
    
signals:
    void outClicked(QVariant v = QVariant(true));
    
protected:
    virtual void attachImpl();
    virtual void detachImpl();    
    
private:
    QGraphicsProxyWidget* m_Item;
};

#endif	/* BUTTON_H */

