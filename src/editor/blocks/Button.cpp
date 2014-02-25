/* 
 * File:   Button.cpp
 * Author: acailly
 * 
 * Created on 25 février 2014, 11:11
 */

#include "Button.h"

#include "editor/FBPEditor.h"
#include "Util.h"

#include <QtGui/QGraphicsScene>
#include <QtGui/QGraphicsProxyWidget>
#include <QtGui/QPushButton>

Button::Button()
: m_Item(NULL)
{
}

Button::~Button()
{
}

void Button::attachImpl()
{
    QPushButton* newButton = new QPushButton();
    newButton->setText("New block");
    m_Item = getEditor()->getScene()->addWidget(newButton);  
    
    CONNECT(newButton, SIGNAL(clicked()), this, SIGNAL(outClicked()));
}
    
void Button::detachImpl()
{
    getEditor()->getScene()->removeItem(m_Item);
    delete m_Item;
    m_Item = NULL;
}

