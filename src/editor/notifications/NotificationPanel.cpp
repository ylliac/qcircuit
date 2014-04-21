/*
 * File:   NotificationPanel.cpp
 * Author: HOME
 *
 * Created on 21 avril 2014, 12:04
 */

#include "NotificationPanel.h"

#include <QtGui/QVBoxLayout>
#include <QtGui/QLabel>

NotificationPanel::NotificationPanel(QWidget *parent, Qt::WindowFlags flags) :
QMainWindow(parent, flags)
{
    widget.setupUi(this);
    
    setStyleSheet("border: 1px solid red");
    
    //TODO ACY TEST
    QVBoxLayout *layout = new QVBoxLayout();
    centralWidget()->setLayout(layout);
    
    QLabel* testLabel = new QLabel("2 selected elements", this);    
    layout->addWidget(testLabel);
}

NotificationPanel::~NotificationPanel() {
}
