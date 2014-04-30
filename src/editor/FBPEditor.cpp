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
#include "action/DeleteBlock.h"
#include "action/DeleteSelectedBlocks.h"
#include "action/SetBlockName.h"

FBPEditor::FBPEditor(QWidget* parent, Qt::WindowFlags windowFlag)
: QMainWindow(parent, windowFlag), ui(new Ui::FBPEditor), m_Scene(new EditorScene(this)), m_ScriptEngine(new ScriptEngine(this))
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
    //Delete block
    DeleteBlock* deleteBlock = new DeleteBlock(this);
    //Delete selected blocks
    DeleteSelectedBlocks* deleteSelectedBlocks = new DeleteSelectedBlocks(this);
    //Set block name
    SetBlockName* setBlockName = new SetBlockName(this);
    
    //------------------------------------------------------------------
    // SCRIPT COMMANDS 
    //------------------------------------------------------------------
    m_ScriptEngine->addScriptCommand("Create a new block", newBlock);
    m_ScriptEngine->addScriptCommand("Delete the block $1", deleteBlock);
    m_ScriptEngine->addScriptCommand("Delete the selected blocks", deleteSelectedBlocks);
    m_ScriptEngine->addScriptCommand("Rename block $1 in block $2", setBlockName);
    
    //------------------------------------------------------------------
    // NOTIFICATIONS
    //------------------------------------------------------------------
    //TODO ACY TEST, déplacer ailleurs ?
    NotificationPanel* notificationPanel = new NotificationPanel(ui->graphicsView);
    BlockNotification* notification = new BlockNotification(this);
    notificationPanel->addNotification(notification);
    
    //TODO ACY Pour le débug
    CONNECT(ui->actionNewBlock, SIGNAL(triggered()), newBlock, SLOT(execute()));    
}

EditorScene* FBPEditor::getScene()
{
    return m_Scene;
}

ScriptEngine* FBPEditor::getScriptEngine()
{
    return m_ScriptEngine;
}

bool FBPEditor::runScriptCommand(QString input)
{
    m_ScriptEngine->runScriptCommand(input);
}
