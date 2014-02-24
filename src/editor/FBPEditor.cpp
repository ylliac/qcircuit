/*
 * File:   FBPEditor.cpp
 * Author: acailly
 *
 * Created on 24 février 2014, 17:48
 */

#include "FBPEditor.h"
#include "ui_FBPEditor.h"

#include <QtGui/QGraphicsScene>
#include <QtGui/QGraphicsRectItem>
#include <QtGui/QPushButton>

FBPEditor::FBPEditor(QWidget* parent, Qt::WindowFlags windowFlag)
: QMainWindow(parent, windowFlag), ui(new Ui::FBPEditor), m_GraphicsScene(new QGraphicsScene(this))
{
    ui->setupUi(this);
    
    ui->graphicsView->setScene(m_GraphicsScene);
    
    initialize();
}

FBPEditor::~FBPEditor()
{
    delete ui;
}

void FBPEditor::initialize()
{
    QPushButton* newBlockButton = new QPushButton(this);
    newBlockButton->setText("New block");
    m_GraphicsScene->addWidget(newBlockButton);   
    
    connect(newBlockButton, SIGNAL(clicked()), this, SLOT(addBlock()));
}

void FBPEditor::addBlock()
{
    QGraphicsRectItem* block = m_GraphicsScene->addRect(20,20,20,20);
    block->setToolTip("Block");
}
