/*
 * File:   MainWindow.cpp
 * Author: acailly
 *
 * Created on 29 janvier 2014, 18:21
 */

#include "MainWindow.h"
#include "ui_MainWindow.h"

#include "../core/FBPComponent.h"
#include "../core/FBPNetwork.h"

#include "../loader/NetworkLoaderFromFBP.h"

#include "../common/Timer.h"
#include "../common/UDPEmitter.h"
#include "../common/UDPReceiver.h"
#include "../common/Console.h"
#include "../common/Test.h"

#include <QtCore/QtConcurrentRun>

#include <iostream>

MainWindow::MainWindow(QWidget* parent, Qt::WindowFlags windowFlag)
: QMainWindow(parent, windowFlag), ui(new Ui::MainWindow), m_Network(NULL)
{
    ui->setupUi(this);

    //------------------------------------------------------------------
    // CREATE CIRCUIT 
    //------------------------------------------------------------------

    NetworkLoaderFromFBP loader;
    loader.addComponentClass("Timer", Timer::staticMetaObject);
    loader.addComponentClass("Console", Console::staticMetaObject);
    loader.addComponentClass("UDPEmitter", UDPEmitter::staticMetaObject);
    loader.addComponentClass("UDPReceiver", UDPReceiver::staticMetaObject);
    m_Network = loader.loadFromFile("../source/resources/demo.fbp");
    m_Network->setParent(this);

    connect(ui->buttonTrigger, SIGNAL(clicked()), this, SLOT(launchNetwork()));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete m_Network;
}

void MainWindow::launchNetwork()
{
//    m_Network->go();        
    QtConcurrent::run(m_Network, &FBPNetwork::go);
    
    //TODO ACY
    std::cout << "End of Network" << std::endl; 
}
