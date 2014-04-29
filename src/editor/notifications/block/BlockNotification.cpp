/*
 * File:   BlockNotification.cpp
 * Author: acailly
 *
 * Created on 29 avril 2014, 18:23
 */

#include "BlockNotification.h"
#include "ui_BlockNotification.h"

BlockNotification::BlockNotification(QWidget* parent, Qt::WindowFlags windowFlag)
: QWidget(parent, windowFlag), ui(new Ui::BlockNotification)
{
    ui->setupUi(this);
    
    setStyleSheet(
            "QFrame#content{"
            "   background-color: white;"
            "   border: 1px solid gray;"
            "   padding: 3px;"
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
    
    setReadOnly(true);    
}

BlockNotification::~BlockNotification()
{
    delete ui;
}

void BlockNotification::on_buttonEdit_clicked()
{
    setReadOnly(false);
}

void BlockNotification::on_buttonValidate_clicked()
{
    setReadOnly(true);
}

void BlockNotification::setReadOnly(bool readOnly)
{
    ui->editName->setReadOnly(readOnly);
    ui->buttonEdit->setVisible(readOnly);
    ui->buttonValidate->setVisible(!readOnly);
}
