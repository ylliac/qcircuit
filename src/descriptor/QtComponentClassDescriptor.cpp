/* 
 * File:   QtComponentClassDescriptor.cpp
 * Author: acailly
 * 
 * Created on 4 juin 2014, 19:02
 */

#include "QtComponentClassDescriptor.h"

QtComponentClassDescriptor::QtComponentClassDescriptor(QMetaObject metaObject) :
m_MetaObject(metaObject)
{
    initialize();
}

QtComponentClassDescriptor::~QtComponentClassDescriptor()
{
}

FBPComponent* QtComponentClassDescriptor::newComponent() const
{
    return qobject_cast<FBPComponent*>(m_MetaObject.newInstance());
}

void QtComponentClassDescriptor::initialize()
{
    setClassName(m_MetaObject.className());
    
    //TODO ACY Parser les Q_CLASSINFO du meta object pour remplir le descriptor    
}

