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
#include "../common/Value.h"
#include "../common/Script.h"

#include "../descriptor/ComponentClassRepository.h"
#include "../descriptor/QtComponentClassDescriptor.h"

#include <QtCore/QtConcurrentRun>

#include <iostream>

MainWindow::MainWindow(QWidget* parent, Qt::WindowFlags windowFlag)
: QMainWindow(parent, windowFlag), ui(new Ui::MainWindow), m_Network(NULL)
{
    ui->setupUi(this);

    //------------------------------------------------------------------
    // CREATE CIRCUIT 
    //------------------------------------------------------------------
    ComponentClassRepository repository;
    repository.addComponentClass(new QtComponentClassDescriptor(Timer::staticMetaObject));
    repository.addComponentClass(new QtComponentClassDescriptor(Console::staticMetaObject));
    repository.addComponentClass(new QtComponentClassDescriptor(UDPEmitter::staticMetaObject));
    repository.addComponentClass(new QtComponentClassDescriptor(UDPReceiver::staticMetaObject));
    repository.addComponentClass(new QtComponentClassDescriptor(Value::staticMetaObject));
    repository.addComponentClass(new QtComponentClassDescriptor(Script::staticMetaObject));
    
    NetworkLoaderFromFBP loader;
//    m_Network = loader.loadFromFile("../source/resources/demo.fbp", &repository);
    m_Network = loader.loadFromFile("../source/resources/neural_network.fbp", &repository);
//    m_Network = loader.loadFromFile("../source/resources/testRivescript.fbp", &repository);
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
    m_Network->activate();
    m_Network->wait();
    
    std::cout << "Network finished" << std::endl;
}
