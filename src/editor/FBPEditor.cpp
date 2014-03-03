/*
 * File:   FBPEditor.cpp
 * Author: acailly
 *
 * Created on 24 février 2014, 17:48
 */

#include "FBPEditor.h"
#include "ui_FBPEditor.h"

#include "blocks/FBPEditorBlock.h"
#include "blocks/Button.h"
#include "blocks/TextPrompt.h"
#include "Util.h"
#include "core/FBPNetwork.h"
#include "network/CreateNewComponent.h"
#include "network/FBPEditorNetwork.h"

#include <iostream>
#include <QtCore/QtConcurrentRun>
#include <QtGui/QGraphicsScene>

FBPEditor::FBPEditor(QWidget* parent, Qt::WindowFlags windowFlag)
: QMainWindow(parent, windowFlag), ui(new Ui::FBPEditor), m_GraphicsScene(new QGraphicsScene(this)), m_Network(new FBPEditorNetwork(this))
{
    ui->setupUi(this);
    
    ui->graphicsView->setScene(m_GraphicsScene);
    
    initialize();
    
    //------------------------------------------------------------------
    // BUILD APP 
    //------------------------------------------------------------------
    Button* newComponentButton = new Button();
    addBlock("New block button", newComponentButton);
    
    TextPrompt* newComponentNamePrompt = new TextPrompt();
    addBlock("New block name prompt", newComponentNamePrompt);
    
    //------------------------------------------------------------------
    // CONNECT THE BLOCKS TO THE NETWORK 
    //------------------------------------------------------------------
    //Button block => Input "TRIGGER"
    m_Network->connectFromSignal(newComponentButton, SIGNAL(outClicked(QVariant)), "TRIGGER");
    
    //Output "NEWCOMPONENT_ASKNAME" => Enter text block
    m_Network->connectToSlot("NEWCOMPONENT_ASKNAME", newComponentNamePrompt, SLOT(inTrigger(QVariant)));
    
    //Enter text block => Input "NEWCOMPONENT_NAME" 
    bool check = m_Network->connectFromSignal(newComponentNamePrompt, SIGNAL(outValue(QVariant)), "NEWCOMPONENT_NAME");
    Q_ASSERT(check);
    
    //------------------------------------------------------------------
    // START THE NETWORK 
    //------------------------------------------------------------------
    m_Network->activate();
}

FBPEditor::~FBPEditor()
{
    delete ui;
}

void FBPEditor::initialize()
{
    //Background color
    m_GraphicsScene->setBackgroundBrush(QBrush(Qt::white));
}

void FBPEditor::addBlock(QString idName, FBPEditorBlock* block)
{
    Q_ASSERT(block != NULL);
    Q_ASSERT(!block->isAttached());    
    Q_ASSERT(!m_Blocks.contains(idName));
    Q_ASSERT(!m_Blocks.values().contains(block));
    
    block->attach(this);
    m_Blocks.insert(idName, block);
}
    
void FBPEditor::removeBlock(FBPEditorBlock* block)
{
    Q_ASSERT(block != NULL);
    Q_ASSERT(block->isAttached());
    Q_ASSERT(m_Blocks.values().contains(block));
    
    block->detach(); 
    m_Blocks.remove(m_Blocks.key(block));
}

void FBPEditor::removeBlock(QString idName)
{
    Q_ASSERT(m_Blocks.contains(idName));
    FBPEditorBlock* block = m_Blocks.value(idName);    
    Q_ASSERT(block != NULL);
    Q_ASSERT(block->isAttached());
    
    block->detach();    
    m_Blocks.remove(idName);
}

FBPEditorBlock* FBPEditor::getBlock(QString idName)
{
    return m_Blocks.value(idName);
}

QGraphicsScene* FBPEditor::getScene()
{
    return m_GraphicsScene;
}

FBPNetwork* FBPEditor::getNetwork()
{
    return m_Network;
}
