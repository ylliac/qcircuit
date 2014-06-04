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
#include <QtGui/QLayout>
#include <QtGui/QPen>
#include <QtGui/QPainter>

#include "scene/EditorScene.h"
#include "cornermenu/CornerMenu.h"
#include "notifications/NotificationPanel.h"
#include "notifications/block/BlockNotification.h"
#include "notifications/search/SearchNotification.h"
#include "action/CreateNewBlock.h"
#include "action/CreateNewArrow.h"
#include "action/DeleteBlock.h"
#include "action/DeleteSelectedBlocks.h"
#include "action/SetBlockName.h"
#include "action/ImportDiagram.h"
#include "action/ExportDiagram.h"
#include "action/Debug.h"
#include "toast/Toast.h"
#include "../descriptor/ComponentClassRepository.h"
#include "../descriptor/QtComponentClassDescriptor.h"
#include "../common/Timer.h"
#include "../common/Console.h"
#include "../common/UDPEmitter.h"
#include "../common/UDPReceiver.h"

FBPEditor::FBPEditor(QWidget* parent, Qt::WindowFlags windowFlag)
: QMainWindow(parent, windowFlag), ui(new Ui::FBPEditor), m_Scene(new EditorScene(this)), m_ScriptEngine(new ScriptEngine(this)) {
    ui->setupUi(this);

    m_ComponentClasses = new ComponentClassRepository();
    m_NotificationPanel = new NotificationPanel(this);

    ui->graphicsView->setScene(m_Scene);
    //    ui->graphicsView->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    ui->graphicsView->setAlignment(Qt::AlignCenter);
    ui->graphicsView->setDragMode(QGraphicsView::RubberBandDrag);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing, true);
    ui->graphicsView->setRenderHint(QPainter::HighQualityAntialiasing, true);
    ui->graphicsView->setRenderHint(QPainter::SmoothPixmapTransform, true);

    initialize();
}

FBPEditor::~FBPEditor() {
    delete ui;
}

void FBPEditor::initialize() {

    //Custom windows
    setWindowFlags(Qt::CustomizeWindowHint);    
    setWindowTitle("FBP Editor");

    //------------------------------------------------------------------
    // TITLE BAR
    //------------------------------------------------------------------
    m_TitleBar = new WindowTitleBar(this);
    QGridLayout* gridLayout = new QGridLayout(ui->topWidget);
    gridLayout->setMargin(0); // No space between window's element and the border
    gridLayout->setSpacing(0); // No space between window's element
    ui->topWidget->setLayout(gridLayout);
    gridLayout->addWidget(m_TitleBar, 0, 0, 1, 1);
    gridLayout->setColumnStretch(0, 0);
    CONNECT(this, SIGNAL(windowTitleChanged()), m_TitleBar, SLOT(updateWindowTitle()));

    //------------------------------------------------------------------
    // CONFIGURATION 
    //------------------------------------------------------------------
    //TODO

    //------------------------------------------------------------------
    // ACTIONS 
    //------------------------------------------------------------------
    //New block
    CreateNewBlock* newBlock = new CreateNewBlock(this);
    m_ScriptEngine->registerAction("CreateBlock", newBlock);
    //Delete block
    DeleteBlock* deleteBlock = new DeleteBlock(this);
    m_ScriptEngine->registerAction("DeleteBlock", deleteBlock);
    //Delete selected blocks
    DeleteSelectedBlocks* deleteSelectedBlocks = new DeleteSelectedBlocks(this);
    m_ScriptEngine->registerAction("DeleteSelectedBlocks", deleteSelectedBlocks);
    //Set block name
    SetBlockName* setBlockName = new SetBlockName(this);
    m_ScriptEngine->registerAction("SetBlockName", setBlockName);
    //New arrow
    CreateNewArrow* newArrow = new CreateNewArrow(this);
    m_ScriptEngine->registerAction("CreateArrow", newArrow);
    //Import diagram
    ImportDiagram* importDiagram = new ImportDiagram(this);
    m_ScriptEngine->registerAction("ImportDiagram", importDiagram);
    //Export diagram
    ExportDiagram* exportDiagram = new ExportDiagram(this);
    m_ScriptEngine->registerAction("ExportDiagram", exportDiagram);
    //Debug
    Debug* debug = new Debug(this);
    m_ScriptEngine->registerAction("Debug", debug);

    //------------------------------------------------------------------
    // SCRIPT COMMANDS 
    //------------------------------------------------------------------
    m_ScriptEngine->loadAssociationFile("../source/resources/commands.txt");

    //------------------------------------------------------------------
    // NOTIFICATIONS
    //------------------------------------------------------------------
    SearchNotification* searchNotification = new SearchNotification(this);
    m_NotificationPanel->addNotification(searchNotification);
    BlockNotification* blockNotification = new BlockNotification(this);
    m_NotificationPanel->addNotification(blockNotification);
    
    //------------------------------------------------------------------
    // CORNER MENU 
    //------------------------------------------------------------------
    new CornerMenu(this);
    
    //------------------------------------------------------------------
    // COMPONENT CLASSES 
    //------------------------------------------------------------------
    m_ComponentClasses->addComponentClass(new QtComponentClassDescriptor(Timer::staticMetaObject));
    m_ComponentClasses->addComponentClass(new QtComponentClassDescriptor(Console::staticMetaObject));
    m_ComponentClasses->addComponentClass(new QtComponentClassDescriptor(UDPEmitter::staticMetaObject));
    m_ComponentClasses->addComponentClass(new QtComponentClassDescriptor(UDPReceiver::staticMetaObject));
}

ComponentClassRepository* FBPEditor::getComponentClassRepository()
{
    return m_ComponentClasses;
}

QGraphicsView* FBPEditor::getGraphicsView() {
    return ui->graphicsView;
}

EditorScene* FBPEditor::getScene() {
    return m_Scene;
}

ScriptEngine* FBPEditor::getScriptEngine() {
    return m_ScriptEngine;
}

NotificationPanel* FBPEditor::getNotificationPanel() {
    return m_NotificationPanel;
}

bool FBPEditor::runScriptCommand(QString input) {
    bool result = m_ScriptEngine->runScriptCommand(input);
    Q_ASSERT(result);
    return result;
}

void FBPEditor::info(QString text, int timeout)
{
    Toast::make(this, text, timeout);
}

void FBPEditor::paintEvent(QPaintEvent *event) {
    QPainter painter(this);

    QBrush background(QColor(23, 23, 34));

    painter.setBrush(background);
    painter.setPen(Qt::NoPen); // No stroke

    painter.drawRect(0, 0, width(), height());
}

void FBPEditor::setWindowTitle(const QString &title) {
    QWidget::setWindowTitle(title);

    emit windowTitleChanged();
}
