/* 
 * File:   ComponentClassRepository.cpp
 * Author: acailly
 * 
 * Created on 4 juin 2014, 18:56
 */

#include "ComponentClassRepository.h"

#include "ComponentClassDescriptor.h"

ComponentClassRepository::ComponentClassRepository()
{
}

ComponentClassRepository::~ComponentClassRepository()
{
}

void ComponentClassRepository::addComponentClass(ComponentClassDescriptor* componentClass)
{
    m_ComponentClasses.insert(componentClass->getClassName(), componentClass);
}
    
ComponentClassDescriptor* ComponentClassRepository::findComponentClass(QString className)
{
    return m_ComponentClasses.value(className);
}

