/*
 * File:   MainWindow.cpp
 * Author: acailly
 *
 * Created on 29 janvier 2014, 18:21
 */

#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <DSPatch.h>
#include "core/QCircuit.h"
#include "core/QComponent.h"

#include "common/Timer.h"
#include "common/Console.h"

MainWindow::MainWindow(QWidget* parent, Qt::WindowFlags windowFlag)
: QMainWindow(parent, windowFlag), ui(new Ui::MainWindow), m_Circuit(NULL)
{
    ui->setupUi(this);

    //------------------------------------------------------------------
    // CREATE CIRCUIT 
    //------------------------------------------------------------------

    m_Circuit = new QCircuit();

    Timer* timer = new Timer();
    Console* console = new Console();

    m_Circuit->AddComponent(timer, "TIMER");
    m_Circuit->AddComponent(console, "CONSOLE");

    m_Circuit->ConnectOutToIn("TIMER.TIME", "CONSOLE.MESSAGE");

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
