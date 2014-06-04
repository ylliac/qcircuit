/* 
 * File:   BlockDescription.cpp
 * Author: acailly
 * 
 * Created on 4 juin 2014, 18:34
 */

#include "ComponentClassDescriptor.h"

ComponentClassDescriptor::ComponentClassDescriptor()
{
}

ComponentClassDescriptor::~ComponentClassDescriptor()
{
}
    
QString ComponentClassDescriptor::getClassName() const
{
    return m_ClassName;
}
    
void ComponentClassDescriptor::setClassName(QString value)
{
    m_ClassName = value;
}
    
QString ComponentClassDescriptor::getDescription() const
{
    return m_Description;
}
    
void ComponentClassDescriptor::setDescription(QString value)
{
    m_Description = value;
}

QList<QString> ComponentClassDescriptor::getInPorts() const
{
    return m_InPorts.keys();
}

QString ComponentClassDescriptor::getInPortDescription(QString portName) const
{
    return m_InPorts.value(portName);
}

void ComponentClassDescriptor::addInPort(QString portName, QString portDescription)
{
    m_InPorts.insert(portName, portDescription);
}

QList<QString> ComponentClassDescriptor::getOutPorts() const
{
    return m_OutPorts.keys();
}

QString ComponentClassDescriptor::getOutPortDescription(QString portName) const
{
    return m_OutPorts.value(portName);
}

void ComponentClassDescriptor::addOutPort(QString portName, QString portDescription)
{
    m_OutPorts.insert(portName, portDescription);
}

FBPComponent* ComponentClassDescriptor::newComponent() const
{
    return NULL;
}

