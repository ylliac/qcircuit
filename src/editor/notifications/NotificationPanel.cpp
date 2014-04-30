/*
 * File:   NotificationPanel.cpp
 * Author: HOME
 *
 * Created on 21 avril 2014, 17:30
 */

#include "NotificationPanel.h"
#include "ui_NotificationPanel.h"

#include <QtGui/QLabel>

#include "editor/FBPEditor.h"

NotificationPanel::NotificationPanel(FBPEditor* editor) :
QWidget(editor->getGraphicsView()), ui(new Ui::NotificationPanel),
m_Editor(editor)
{
    ui->setupUi(this);
    
    int fixedWidth = 300;
    
    //Size
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
    setMinimumWidth(fixedWidth);
    setGeometry(0,0,fixedWidth,10000);
        
    //Layout
    m_Layout = new QVBoxLayout();
    m_Layout->setAlignment(Qt::AlignTop);
    setLayout(m_Layout);
    
    //Style
    setStyleSheet(
            "QFrame{"
            "   background-color: white;"
            "   border: 1px solid gray;"
            "   padding: 3px;"
            "   margin: 0px;"
            "}"
            "QPushButton{"
            "   border: none;"
            "   padding: 5px;"
            "}"
            "QPushButton:hover{"
            "   border: 1px solid #C6C6C6;"
            "   background-color: #F4F4F4;"
            "}"
            "QLineEdit{"
            "   border: 2px solid gray;"
            "   padding: 2px;"
            "}" 
            "QLineEdit:read-only {"
            "   background: white;"
            "   border: none;"
            "}"     
    );
}

NotificationPanel::~NotificationPanel() {
}

void NotificationPanel::addNotification(QWidget* notification)
{
    m_Layout->addWidget(notification);
    m_Layout->setStretchFactor(notification, 0);
    m_Layout->setSpacing(0);
}
