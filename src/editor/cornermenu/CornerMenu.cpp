/*
 * File:   CornerMenu.cpp
 * Author: acailly
 *
 * Created on 16 mai 2014, 09:37
 */

#include "CornerMenu.h"
#include "ui_CornerMenu.h"

#include <QtCore/QEvent>

#include "util/Util.h"
#include "editor/FBPEditor.h"

CornerMenu::CornerMenu(FBPEditor* editor)
: QWidget(editor->getGraphicsView()), ui(new Ui::CornerMenu),
m_Editor(editor)
{
    ui->setupUi(this);

    //Style
    setStyleSheet(
            "QWidget{"
            "   background-color: transparent;"
            "   border: 1px solid gray;"
            "   padding: 3px;"
            "   margin: 0px;"
            "}"
            "QPushButton{"
            "   border: none;"
            "   padding: 5px;"
            "}"
            "QPushButton:hover{"
            "   border: 1px solid #C6C6C6;"
            "   background-color: #F4F4F4;"
            "}"
            "QPushButton:pressed{"
            "   border: 1px solid black;"
            "   background-color: #F4F4F4;"
            "}"
            "QPushButton:checked{"
            "   border: 1px solid #C6C6C6;"
            "   background-color: #C6C6C6;"
            "}"
            );

    ui->menuButton->setVisible(true);

    ui->buttonDebug->setVisible(false);
    ui->buttonExport->setVisible(false);
    ui->buttonProfile->setVisible(false);
    ui->buttonImport->setVisible(false);
    ui->buttonSnapshot->setVisible(false);

    updatePosition();
    parent()->installEventFilter(this);
}

CornerMenu::~CornerMenu()
{
    delete ui;
}

void CornerMenu::on_menuButton_toggled(bool show)
{    
    if(show)
    {
        Util::fadeIn(ui->buttonDebug);
        Util::fadeIn(ui->buttonExport);
        Util::fadeIn(ui->buttonProfile);
        Util::fadeIn(ui->buttonImport);
        Util::fadeIn(ui->buttonSnapshot);
    }
    else
    {
        Util::fadeOut(ui->buttonDebug);
        Util::fadeOut(ui->buttonExport);
        Util::fadeOut(ui->buttonProfile);
        Util::fadeOut(ui->buttonImport);
        Util::fadeOut(ui->buttonSnapshot);
    }
}

bool CornerMenu::eventFilter(QObject *, QEvent * event)
{
    if (event->type() == QEvent::Resize)
    {
        updatePosition();
    }
    return false;
}

void CornerMenu::updatePosition()
{
    QSize parentSize = parentWidget()->size();
    int x = parentSize.width() - width();
    int y = parentSize.height() - height();

    setGeometry(x, y, width(), height());
}

void CornerMenu::on_buttonDebug_clicked()
{
    //TODO
}

void CornerMenu::on_buttonProfile_clicked()
{
    //TODO
}

void CornerMenu::on_buttonExport_clicked()
{    
    m_Editor->runScriptCommand(
        QString("Export diagram")
    );
}

void CornerMenu::on_buttonImport_clicked()
{
    m_Editor->runScriptCommand(
        QString("Import diagram")
    );
}

void CornerMenu::on_buttonSnapshot_clicked()
{
    //TODO
}
