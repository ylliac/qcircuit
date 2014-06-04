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
            "QFrame#line{"
            "   background-color: black;"
            "   border: 1px solid black;"
            "   margin: 0px;"
            "}"            
            "QLabel{"
            "   border: none;"
            "   margin: 0px;"
            "   font-size: 12px;"
            "   font-weight: bold;"
            "}"
            "QLabel#title{"
            "   border: none;"
            "   margin: 0px;"
            "   font-size: 15px;"
            "   font-weight: bold;"
            "}"
            "QPushButton{"
            "   border: none;"
            "   padding: 5px;"
            "}"
            "QPushButton:hover{"
            "   border: 1px solid #C6C6C6;"
            "   background-color: #F4F4F4;"
            "}"
            "QPushButton:pressed{"
            "   border: 1px solid black;"
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
            "QGroupBox::title {"
            "    subcontrol-origin: margin;"
            "    subcontrol-position: top center; /* position at the top center */"
            "    padding: 0 3px;"
            "    background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,stop: 0 #FFOECE, stop: 1 #FFFFFF);"
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
