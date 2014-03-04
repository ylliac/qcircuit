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
#include <QtGui/QGraphicsScene>

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
    //Background color
    m_GraphicsScene->setBackgroundBrush(QBrush(Qt::white));
}

QGraphicsScene* FBPEditor::getScene()
{
    return m_GraphicsScene;
}
