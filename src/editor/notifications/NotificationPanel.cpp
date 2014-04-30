/*
 * File:   NotificationPanel.cpp
 * Author: HOME
 *
 * Created on 21 avril 2014, 17:30
 */

#include "NotificationPanel.h"

#include <QtGui/QLabel>

NotificationPanel::NotificationPanel(QWidget* parent, Qt::WindowFlags f) :
QWidget(parent, f)
{
    widget.setupUi(this);
    
    int fixedWidth = 300;
    
    //Size
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
    setMinimumWidth(fixedWidth);
    setGeometry(0,0,fixedWidth,10000);
        
    //Layout
    m_Layout = new QVBoxLayout();
    m_Layout->setAlignment(Qt::AlignTop);
    setLayout(m_Layout);
}

NotificationPanel::~NotificationPanel() {
}

void NotificationPanel::addNotification(QWidget* notification)
{
    m_Layout->addWidget(notification);
    m_Layout->setStretchFactor(notification, 0);
}
