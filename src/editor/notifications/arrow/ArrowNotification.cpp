/*
 * File:   ArrowNotification.cpp
 * Author: acailly
 *
 * Created on 5 juin 2014, 17:30
 */

#include "ArrowNotification.h"
#include "ui_ArrowNotification.h"

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

ArrowNotification::ArrowNotification(FBPEditor* editor) :
QWidget(editor), ui(new Ui::ArrowNotification),
m_Editor(editor)
{
    ui->setupUi(this);
    
    setReadOnly(true);  
    setVisible(false);  
    
    CONNECT(m_Editor->getScene(), SIGNAL(selectionChanged()), this, SLOT(onSelectionChanged()));    
}

ArrowNotification::~ArrowNotification()
{
    delete ui;
}

void ArrowNotification::on_buttonEdit_clicked()
{
    setReadOnly(false);
}

void ArrowNotification::on_buttonValidate_clicked()
{
    setSelectedFromPortName(ui->editFrom->text());    
    setReadOnly(true);
}

void ArrowNotification::on_buttonCancel_clicked()
{    
    setReadOnly(true);
}

void ArrowNotification::on_buttonDelete_clicked()
{
    deleteSelectedBlock();
}

void ArrowNotification::on_editFrom_returnPressed()
{
    setSelectedFromPortName(ui->editFrom->text());    
    setReadOnly(true);
}

void ArrowNotification::onSelectionChanged()
{
    //Cancel edition
    setReadOnly(true);
    
    //Hide or Display 
    bool currentState = isVisible();
    bool futureState = SceneDetective::getSelectedArrows(m_Editor->getScene()).size() == 1;
    
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

void ArrowNotification::setReadOnly(bool readOnly)
{
    ui->editFrom->setText(selectedFromPortName());
    ui->editFrom->setReadOnly(readOnly);
    
    ui->buttonEdit->setVisible(readOnly);
    ui->buttonDelete->setVisible(readOnly);
    
    ui->buttonValidate->setVisible(!readOnly);
    ui->buttonCancel->setVisible(!readOnly);
}

QString ArrowNotification::selectedFromPortName()
{
    QString result;
    
    QList<ArrowItem*> selectedArrows = SceneDetective::getSelectedArrows(m_Editor->getScene());
    if(selectedArrows.size() == 1)
    {
        result = selectedArrows.first()->getOutputPortName();
    }
    
    return result;
}

void ArrowNotification::setSelectedFromPortName(QString name)
{    
    QList<ArrowItem*> selectedArrows = SceneDetective::getSelectedArrows(m_Editor->getScene());
    if(selectedArrows.size() == 1)
    {
        //TODO ACY
//        m_Editor->runScriptCommand(
//            QString("Rename block %1 in block %2")
//            .arg(selectedBlocks.first()->name())
//            .arg(name)
//        );
        m_Editor->info("Renaiming is not implemented yet.");
    }
}

void ArrowNotification::deleteSelectedBlock()
{
    m_Editor->runScriptCommand(
        QString("Delete selected blocks")
    );
}
