/*
 * File:   MainWindow.cpp
 * Author: acailly
 *
 * Created on 29 janvier 2014, 18:21
 */

#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <DSPatch.h>
#include "../core/QCircuit.h"
#include "../core/QComponent.h"

#include "../loader/CircuitLoaderFromFBP.h"

#include "../common/Timer.h"
#include "../common/UDPEmitter.h"
#include "../common/UDPReceiver.h"
#include "../common/Console.h"

MainWindow::MainWindow(QWidget* parent, Qt::WindowFlags windowFlag)
: QMainWindow(parent, windowFlag), ui(new Ui::MainWindow), m_Circuit(NULL)
{
    ui->setupUi(this);

    //------------------------------------------------------------------
    // CREATE CIRCUIT 
    //------------------------------------------------------------------

    CircuitLoaderFromFBP loader;
    loader.addComponentClass("Timer", Timer::staticMetaObject);
    loader.addComponentClass("Console", Console::staticMetaObject);
    loader.addComponentClass("UDPEmitter", UDPEmitter::staticMetaObject);
    loader.addComponentClass("UDPReceiver", UDPReceiver::staticMetaObject);
    m_Circuit = loader.loadFromFile("../source/resources/demo.fbp");

    connect(ui->buttonTrigger, SIGNAL(clicked()), this, SLOT(launchCircuit()));
}

MainWindow::~MainWindow()
{
    delete ui;

    DSPatch::Finalize();
    delete m_Circuit;
}

void MainWindow::launchCircuit()
{
    m_Circuit->StartAutoTick();
    m_Circuit->SetThreadCount(4);
}
