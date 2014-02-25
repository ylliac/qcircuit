/* 
 * File:   GUIThreadExecutor.cpp
 * Author: acailly
 * 
 * Created on 25 février 2014, 17:29
 */

#include "GUIThreadExecutor.h"

#include <QtGui/QApplication>
#include <QtCore/QMetaType>

GUIThreadExecutor::GUIThreadExecutor()
{
    qRegisterMetaType<const char*>("const char *");
    
    //Move to GUI thread
    moveToThread(QApplication::instance()->thread());
}

GUIThreadExecutor::~GUIThreadExecutor()
{
}

void GUIThreadExecutor::execute(QObject* obj, const char* member, bool blocking)
{
    if(blocking)
    {
        QMetaObject::invokeMethod(this,"executionRequested", Qt::BlockingQueuedConnection, Q_ARG(QObject*, obj), Q_ARG(const char*, member));
    }
    else
    {
        QMetaObject::invokeMethod(this,"executionRequested", Qt::QueuedConnection, Q_ARG(QObject*, obj), Q_ARG(const char*, member));
    }
}

void GUIThreadExecutor::executionRequested(QObject* obj, const char* member)
{
    Q_ASSERT(thread() == QApplication::instance()->thread());
    
    QMetaObject::invokeMethod(obj,member, Qt::DirectConnection);
}

