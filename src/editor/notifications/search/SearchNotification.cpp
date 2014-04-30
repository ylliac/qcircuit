/*
 * File:   SearchNotification.cpp
 * Author: HOME
 *
 * Created on 30 avril 2014, 21:50
 */

#include "SearchNotification.h"
#include "ui_SearchNotification.h"

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


SearchNotification::SearchNotification(FBPEditor* editor)
: QWidget(editor), ui(new Ui::SearchNotification),
m_Editor(editor)
{
    ui->setupUi(this);    
}

SearchNotification::~SearchNotification() {
}

void SearchNotification::on_buttonAdd_clicked()
{
    m_Editor->runScriptCommand(
        QString("Create a new block")
    );
}
