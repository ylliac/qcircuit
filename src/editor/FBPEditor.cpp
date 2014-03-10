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

#include "action/CreateNewBlock.h"
#include "scene/EditorScene.h"
#include "scene/DefaultState.h"

FBPEditor::FBPEditor(QWidget* parent, Qt::WindowFlags windowFlag)
: QMainWindow(parent, windowFlag), ui(new Ui::FBPEditor), m_Scene(new EditorScene(this))
{
    ui->setupUi(this);
    
    ui->graphicsView->setScene(m_Scene);
    ui->graphicsView->setDragMode(QGraphicsView::RubberBandDrag);
    
//    ui->graphicsView->installEventFilter(new DefaultState(ui->graphicsView));
    
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
    
}

EditorScene* FBPEditor::getScene()
{
    return m_Scene;
}
