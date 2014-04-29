/*
 * File:   FBPEditor.cpp
 * Author: acailly
 *
 * Created on 24 février 2014, 17:48
 */

#include "FBPEditor.h"
#include "ui_FBPEditor.h"
#include "Util.h"

#include <iostream>
#include <QtCore/QtConcurrentRun>
#include <QtGui/QLabel>

#include "action/CreateNewBlock.h"
#include "scene/EditorScene.h"
#include "notifications/NotificationPanel.h"
#include "notifications/block/BlockNotification.h"

FBPEditor::FBPEditor(QWidget* parent, Qt::WindowFlags windowFlag)
: QMainWindow(parent, windowFlag), ui(new Ui::FBPEditor), m_Scene(new EditorScene(this))
{
    ui->setupUi(this);
    
    ui->graphicsView->setScene(m_Scene);
//    ui->graphicsView->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    ui->graphicsView->setAlignment(Qt::AlignCenter);
    ui->graphicsView->setDragMode(QGraphicsView::RubberBandDrag);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing, true);
    ui->graphicsView->setRenderHint(QPainter::HighQualityAntialiasing, true);
    ui->graphicsView->setRenderHint(QPainter::SmoothPixmapTransform, true);
    
    initialize();
}

FBPEditor::~FBPEditor()
{
    delete ui;
}

void FBPEditor::initialize()
{   
    //------------------------------------------------------------------
    // CONFIGURATION 
    //------------------------------------------------------------------
    //TODO
    
    //------------------------------------------------------------------
    // ACTIONS 
    //------------------------------------------------------------------
    //New block
    CreateNewBlock* newBlock = new CreateNewBlock(this);
    CONNECT(ui->actionNewBlock, SIGNAL(triggered()), newBlock, SLOT(execute()));    
    
    //------------------------------------------------------------------
    // NOTIFICATIONS
    //------------------------------------------------------------------
    //TODO ACY TEST, déplacer ailleurs ?
    NotificationPanel* notificationPanel = new NotificationPanel(ui->graphicsView);
    BlockNotification* notification = new BlockNotification(ui->graphicsView);
    notificationPanel->addNotification(notification);
}

EditorScene* FBPEditor::getScene()
{
    return m_Scene;
}
