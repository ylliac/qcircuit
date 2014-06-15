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
    
    setReadOnlyFrom(true);  
    setReadOnlyTo(true);  
    setVisible(false);  
    
    CONNECT(m_Editor->getScene(), SIGNAL(selectionChanged()), this, SLOT(onSelectionChanged()));    
}

ArrowNotification::~ArrowNotification()
{
    delete ui;
}

void ArrowNotification::on_buttonEditFrom_clicked()
{
    setReadOnlyFrom(false);
}

void ArrowNotification::on_buttonEditTo_clicked()
{
    setReadOnlyTo(false);
}

void ArrowNotification::on_buttonValidateFrom_clicked()
{
    setSelectedFromPortName(ui->editFrom->text());    
    setReadOnlyFrom(true);
}

void ArrowNotification::on_buttonValidateTo_clicked()
{
    setSelectedToPortName(ui->editTo->text());    
    setReadOnlyTo(true);
}

void ArrowNotification::on_buttonCancelFrom_clicked()
{    
    setReadOnlyFrom(true);
}

void ArrowNotification::on_buttonCancelTo_clicked()
{    
    setReadOnlyTo(true);
}

void ArrowNotification::on_buttonDelete_clicked()
{
    deleteSelectedArrows();
}

void ArrowNotification::on_editFrom_returnPressed()
{
    setSelectedFromPortName(ui->editFrom->text());    
    setReadOnlyFrom(true);
}

void ArrowNotification::on_editTo_returnPressed()
{
    setSelectedToPortName(ui->editTo->text());    
    setReadOnlyTo(true);
}

void ArrowNotification::onSelectionChanged()
{
    //Cancel edition
    setReadOnlyFrom(true);
    setReadOnlyTo(true);
    
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

void ArrowNotification::setReadOnlyFrom(bool readOnly)
{
    ui->editFrom->setText(selectedFromPortName());
    ui->editFrom->setReadOnly(readOnly);
    
    ui->buttonEditFrom->setVisible(readOnly);
    
    ui->buttonValidateFrom->setVisible(!readOnly);
    ui->buttonCancelFrom->setVisible(!readOnly);
}

void ArrowNotification::setReadOnlyTo(bool readOnly)
{
    ui->editTo->setText(selectedToPortName());
    ui->editTo->setReadOnly(readOnly);
    
    ui->buttonEditTo->setVisible(readOnly);
    
    ui->buttonValidateTo->setVisible(!readOnly);
    ui->buttonCancelTo->setVisible(!readOnly);
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

QString ArrowNotification::selectedToPortName()
{
    QString result;
    
    QList<ArrowItem*> selectedArrows = SceneDetective::getSelectedArrows(m_Editor->getScene());
    if(selectedArrows.size() == 1)
    {
        result = selectedArrows.first()->getInputPortName();
    }
    
    return result;
}

void ArrowNotification::setSelectedFromPortName(QString name)
{    
    QList<ArrowItem*> selectedArrows = SceneDetective::getSelectedArrows(m_Editor->getScene());
    if(selectedArrows.size() == 1)
    {
        m_Editor->runScriptCommand(
            QString("Rename selected arrow from port in %1")
            .arg(name)
        );
    }
}

void ArrowNotification::setSelectedToPortName(QString name)
{    
    QList<ArrowItem*> selectedArrows = SceneDetective::getSelectedArrows(m_Editor->getScene());
    if(selectedArrows.size() == 1)
    {
        m_Editor->runScriptCommand(
            QString("Rename selected arrow to port in %1")
            .arg(name)
        );
    }
}

void ArrowNotification::deleteSelectedArrows()
{
    m_Editor->runScriptCommand(
        QString("Delete selected arrows")
    );
}
