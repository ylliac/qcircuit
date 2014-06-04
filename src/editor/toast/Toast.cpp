/*
 * File:   Toast.cpp
 * Author: acailly
 *
 * Created on 4 juin 2014, 12:28
 */

#include "Toast.h"
#include "ui_Toast.h"

#include "editor/FBPEditor.h"

#include <QtCore/QTimer>
#include <QtGui/QGraphicsDropShadowEffect>

Toast::Toast(QWidget* parent, Qt::WindowFlags windowFlag)
: QWidget(parent, windowFlag), ui(new Ui::Toast)
{
    ui->setupUi(this);
    
    //Style
    setStyleSheet(
            "QWidget{"
            "   background-color: #606060;"
            "   border: none;"
            "   padding: 0px;"
            "   margin: 0px;"
            "}"
            "QLabel{"
            "   font-weight: bold;"
            "   font-size: 12px;"
            "   color: white;"
            "}"     
    );
    
    QGraphicsDropShadowEffect* effect = new QGraphicsDropShadowEffect(this);
    effect->setColor(Qt::lightGray);
    effect->setBlurRadius(20);
    this->setGraphicsEffect(effect);
    
    parent->installEventFilter(this);
}

Toast::~Toast()
{
    delete ui;
}

void Toast::make(FBPEditor* editor, QString text)
{
    Toast* toast = new Toast(editor->getGraphicsView());
    toast->setText(text);
    toast->setVisible(true);
    toast->updatePosition();
    
    QTimer::singleShot(2000, toast, SLOT(close()));
}

QString Toast::text()
{
    return ui->label->text();
}

void Toast::setText(QString text)
{
    ui->label->setText(text);
    adjustSize();
    updatePosition();
}

bool Toast::eventFilter(QObject *, QEvent * event)
{
    if (event->type() == QEvent::Resize)
    {
        updatePosition();
    }
    return false;
}

void Toast::updatePosition()
{
    QSize parentSize = parentWidget()->size();
    int x = parentSize.width() / 2 - width() / 2;
    int y = parentSize.height() - height() - 20;

    setGeometry(x, y, width(), height());
}