/*
 * File:   MainWindow.cpp
 * Author: acailly
 *
 * Created on 29 janvier 2014, 18:21
 */

#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <DSPatch.h>
#include <dspatch/DspCircuit.h>
#include <dspatch/DspComponent.h>

#include "ReadTextFile.h"
#include "ParseLine.h"
#include "StringCondition.h"
#include "AppendToTextEdit.h"
#include "Dispatcher.h"
#include "Producer.h"
#include "Reader.h"
#include "IIP.h"
#include "UDPEmitter.h"
#include "UDPReceiver.h"

MainWindow::MainWindow(QWidget* parent, Qt::WindowFlags windowFlag)
: QMainWindow(parent, windowFlag), ui(new Ui::MainWindow), m_Circuit(NULL)
{
    ui->setupUi(this);

    //------------------------------------------------------------------
    // CREATE CIRCUIT 
    //------------------------------------------------------------------

    m_Circuit = new DspCircuit();

//    ReadTextFile* readTextFile = new ReadTextFile("V:\\prjtests\\dspatch_test\\dspatch-demo\\gpmcc.log");
//    Dispatcher* dispatcher = new Dispatcher();
//    StringCondition* debugCondition = new StringCondition("DEBUG");
//    StringCondition* infoCondition = new StringCondition("INFO");
//    StringCondition* warnCondition = new StringCondition("WARN");
//    AppendToTextEdit* appendToDebug = new AppendToTextEdit(ui->listDebug);
//    AppendToTextEdit* appendToInfo = new AppendToTextEdit(ui->listInfo);
//    AppendToTextEdit* appendToWarn = new AppendToTextEdit(ui->listWarn);
//    Producer* producer = new Producer(2000);
    Producer* producer2 = new Producer(1000);
//    IIP* iip = new IIP();
    Reader* reader = new Reader();
    UDPEmitter* udpEmitter = new UDPEmitter();
    UDPReceiver* udpReceiver = new UDPReceiver();

//    m_Circuit->AddComponent(readTextFile);
//    m_Circuit->AddComponent(dispatcher);
//    m_Circuit->AddComponent(debugCondition);
//    m_Circuit->AddComponent(infoCondition);
//    m_Circuit->AddComponent(warnCondition);
//    m_Circuit->AddComponent(appendToDebug);
//    m_Circuit->AddComponent(appendToInfo);
//    m_Circuit->AddComponent(appendToWarn);
    m_Circuit->AddComponent(producer2);
//    m_Circuit->AddComponent(producer);
    m_Circuit->AddComponent(reader, "Reader");
//    m_Circuit->AddComponent(iip);
    m_Circuit->AddComponent(udpEmitter);
    m_Circuit->AddComponent(udpReceiver);

//    m_Circuit->ConnectOutToIn(readTextFile, "OUT", infoCondition, "IN");
//    m_Circuit->ConnectOutToIn(infoCondition, "OUT", appendToInfo, "IN");
//    m_Circuit->ConnectOutToIn(producer2, "OUT", reader, "IN");
//    m_Circuit->ConnectOutToIn(producer, "OUT", reader, "IN");
//    m_Circuit->ConnectOutToIn(iip, "OUT", reader, "IN");
    m_Circuit->ConnectOutToIn(producer2, "OUT", udpEmitter, "IN");
    m_Circuit->ConnectOutToIn(udpReceiver, "OUT", reader, "IN");

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
//        for( unsigned short i = 0; i < 10; i++ )
//        {
//          m_Circuit->Tick();
//          m_Circuit->Reset();
//        }

    m_Circuit->StartAutoTick();
    m_Circuit->SetThreadCount(4);
    
    //TODO ACY Modification à la volée
    Producer* producer = new Producer(2000);
    m_Circuit->AddComponent(producer);
    m_Circuit->ConnectOutToIn(producer, "OUT", "Reader", "IN");
}
