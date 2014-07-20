/*
 * File:   BlockNotification.cpp
 * Author: acailly
 *
 * Created on 29 avril 2014, 18:23
 */

#include "BlockNotification.h"
#include "ui_BlockNotification.h"

#include <iostream>

#include <QtGui/QGraphicsScene>
#include <QtGui/QGraphicsOpacityEffect>
#include <QtCore/QPropertyAnimation>
#include <QtCore/QEasingCurve>
#include <QtCore/QAbstractAnimation>

#include "editor/FBPEditor.h"
#include "editor/scene/EditorScene.h"
#include "editor/scene/SceneDetective.h"
#include "editor/scene/BlockItem.h"
#include "util/Util.h"
#include "editor/action/DeleteSelectedBlocks.h"
#include "editor/action/SetBlockName.h"
#include "AppendToTextEdit.h"
#include "descriptor/ComponentClassRepository.h"

BlockNotification::BlockNotification(FBPEditor* editor) :
QWidget(editor), ui(new Ui::BlockNotification),
m_Editor(editor)
{
    ui->setupUi(this);
    
    //Initialize component classes choices
    QStringList classNames = m_Editor->getComponentClassRepository()->findAllComponentClassNames();
    //Add the empty choice
    classNames.insert(0, "");
    ui->editType->insertItems(0, classNames);
        
    setReadOnly(true);  
    setVisible(false);  
        
    CONNECT(m_Editor->getScene(), SIGNAL(selectionChanged()), this, SLOT(onSelectionChanged()));    
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

void BlockNotification::on_editType_currentIndexChanged(const QString& text)
{
    setSelectedBlockClass(text);
}

void BlockNotification::onSelectionChanged()
{
    //Cancel edition
    setReadOnly(true);
    QString className = selectedBlockClass();
    int index = ui->editType->findText(selectedBlockClass());
    ui->editType->setCurrentIndex(index == -1 ? 0 : index);
    
    //Hide or Display 
    bool currentState = isVisible();
    bool futureState = SceneDetective::getSelectedBlocks(m_Editor->getScene()).size() == 1;
    
    double startOpacity;
    double endOpacity;
    if(currentState)
    {
        startOpacity = 1.0;
    }
    else
    {
        startOpacity = 0.0;
    }
    if(futureState)
    {
        endOpacity = 1.0;
    }
    else
    {
        endOpacity = 0.0;
    }
    
    if(currentState != futureState)
    {
        if(futureState){
            setVisible(true);
        }
        
        QGraphicsOpacityEffect* opacityEffect = new QGraphicsOpacityEffect(this);
        opacityEffect->setOpacity(startOpacity);
        ui->content->setGraphicsEffect(opacityEffect);
        
        QPropertyAnimation* animation = new QPropertyAnimation(this);
        animation->setTargetObject(opacityEffect);
        animation->setPropertyName("opacity");
        animation->setDuration(200);
        animation->setStartValue(opacityEffect->opacity());
        animation->setEndValue(endOpacity);
        animation->setEasingCurve(QEasingCurve::OutQuad);
        animation->start(QAbstractAnimation::DeleteWhenStopped);
        
        if(!futureState){
            CONNECT(animation, SIGNAL(finished()), this, SLOT(hide()));      
        }
    }
}

void BlockNotification::setReadOnly(bool readOnly)
{
    ui->editName->setText(selectedBlockName());
    ui->editName->setReadOnly(readOnly);
    
    ui->buttonEdit->setVisible(readOnly);
    
    ui->buttonValidate->setVisible(!readOnly);
    ui->buttonCancel->setVisible(!readOnly);
}

QString BlockNotification::selectedBlockName()
{
    QString result;
    
    QList<BlockItem*> selectedBlocks = SceneDetective::getSelectedBlocks(m_Editor->getScene());
    if(selectedBlocks.size() == 1)
    {
        result = selectedBlocks.first()->name();
    }
    
    return result;
}

void BlockNotification::setSelectedBlockName(QString name)
{
    QList<BlockItem*> selectedBlocks = SceneDetective::getSelectedBlocks(m_Editor->getScene());
    if(selectedBlocks.size() == 1)
    {
        m_Editor->runScriptCommand(
            QString("Rename block %1 in block %2")
            .arg(selectedBlocks.first()->name())
            .arg(name)
        );
    }
}

QString BlockNotification::selectedBlockClass()
{
    QString result;
    
    QList<BlockItem*> selectedBlocks = SceneDetective::getSelectedBlocks(m_Editor->getScene());
    if(selectedBlocks.size() == 1)
    {
        result = selectedBlocks.first()->className();
    }
    
    return result;
}
    
void BlockNotification::setSelectedBlockClass(QString className)
{
    QList<BlockItem*> selectedBlocks = SceneDetective::getSelectedBlocks(m_Editor->getScene());
    if(selectedBlocks.size() == 1)
    {
        m_Editor->runScriptCommand(
            QString("Set the class %2 to block %1")
            .arg(selectedBlocks.first()->name())    
            .arg(className)
        );
    }
}

void BlockNotification::deleteSelectedBlock()
{
    m_Editor->runScriptCommand(
        QString("Delete selected blocks")
    );
}
