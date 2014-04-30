/*
 * File:   BlockNotification.cpp
 * Author: acailly
 *
 * Created on 29 avril 2014, 18:23
 */

#include "BlockNotification.h"
#include "ui_BlockNotification.h"

#include "editor/scene/SceneDetective.h"
#include "editor/scene/BlockItem.h"
#include "util/Util.h"
#include "editor/action/DeleteSelectedBlocks.h"
#include "editor/action/SetBlockName.h"

BlockNotification::BlockNotification(QGraphicsScene* scene, QWidget* parent, Qt::WindowFlags windowFlag)
: QWidget(parent, windowFlag), ui(new Ui::BlockNotification),
m_Scene(scene)
{
    ui->setupUi(this);
    
    setStyleSheet(
            "QFrame#content{"
            "   background-color: white;"
            "   border: 1px solid gray;"
            "   padding: 3px;"
            "}"
            "QPushButton{"
            "   border: none;"
            "   padding: 5px;"
            "}"
            "QPushButton:hover{"
            "   border: 1px solid #C6C6C6;"
            "   background-color: #F4F4F4;"
            "}"
            "QLineEdit{"
            "   border: 2px solid gray;"
            "   padding: 2px;"
            "}" 
            "QLineEdit:read-only {"
            "   background: white;"
            "   border: none;"
            "}"     
    );
    
    setReadOnly(true);  
    setVisible(false);  
    
    CONNECT(m_Scene, SIGNAL(selectionChanged()), this, SLOT(on_selection_changed()));    
}

BlockNotification::~BlockNotification()
{
    delete ui;
}

void BlockNotification::on_buttonEdit_clicked()
{
    setReadOnly(false);
}

void BlockNotification::on_buttonValidate_clicked()
{
    setSelectedBlockName(ui->editName->text());    
    setReadOnly(true);
}

void BlockNotification::on_buttonCancel_clicked()
{    
    setReadOnly(true);
}

void BlockNotification::on_buttonDelete_clicked()
{
    deleteSelectedBlock();
}

void BlockNotification::on_editName_returnPressed()
{
    setSelectedBlockName(ui->editName->text());    
    setReadOnly(true);
}

void BlockNotification::on_selection_changed()
{
    //Cancel edition
    setReadOnly(true);
    
    //Hide or Display 
    bool visible = SceneDetective::getSelectedBlocks(m_Scene).size() == 1;
    setVisible(visible);
}

void BlockNotification::setReadOnly(bool readOnly)
{
    ui->editName->setText(selectedBlockName());
    ui->editName->setReadOnly(readOnly);
    
    ui->buttonEdit->setVisible(readOnly);
    ui->buttonDelete->setVisible(readOnly);
    
    ui->buttonValidate->setVisible(!readOnly);
    ui->buttonCancel->setVisible(!readOnly);
}

QString BlockNotification::selectedBlockName()
{
    QString result;
    
    QList<BlockItem*> selectedBlocks = SceneDetective::getSelectedBlocks(m_Scene);
    if(selectedBlocks.size() == 1)
    {
        result = selectedBlocks.first()->name();
    }
    
    return result;
}

void BlockNotification::setSelectedBlockName(QString name)
{
    QList<BlockItem*> selectedBlocks = SceneDetective::getSelectedBlocks(m_Scene);
    if(selectedBlocks.size() == 1)
    {
        SetBlockName action(selectedBlocks.first(), name);
        action.execute();
    }
}

void BlockNotification::deleteSelectedBlock()
{
    DeleteSelectedBlocks deleteAction(m_Scene);
    deleteAction.execute();
}
