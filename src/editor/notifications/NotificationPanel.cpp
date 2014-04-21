/*
 * File:   NotificationPanel.cpp
 * Author: HOME
 *
 * Created on 21 avril 2014, 17:30
 */

#include "NotificationPanel.h"

#include <QtGui/QVBoxLayout>
#include <QtGui/QLabel>

NotificationPanel::NotificationPanel(QWidget* parent, Qt::WindowFlags f) :
QWidget(parent, f)
{
    widget.setupUi(this);
    
    int fixedWidth = 300;
    
    setStyleSheet("QWidget{ border: 1px solid border; background-color:white; }");
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
    setMinimumWidth(fixedWidth);
    setGeometry(0,0,fixedWidth,500);
    
    //TODO ACY TEST
    QVBoxLayout *layout = new QVBoxLayout();
    setLayout(layout);
    
    for (int i = 0; i < 10; i++) {
        QLabel* testLabel = new QLabel("2 selected elements", this);    
        layout->addWidget(testLabel);
    }
}

NotificationPanel::~NotificationPanel() {
}
