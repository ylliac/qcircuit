/* 
 * File:   ComponentClassRepository.h
 * Author: acailly
 *
 * Created on 4 juin 2014, 18:56
 */

#ifndef COMPONENTCLASSREPOSITORY_H
#define	COMPONENTCLASSREPOSITORY_H

#include <QtCore/QString>
#include <QtCore/QMap>

class ComponentClassDescriptor;

class ComponentClassRepository {
public:
    ComponentClassRepository();
    virtual ~ComponentClassRepository();
    
    void addComponentClass(ComponentClassDescriptor* componentClass);
    ComponentClassDescriptor* findComponentClass(QString className);
    
private:
    QMap<QString, ComponentClassDescriptor*> m_ComponentClasses;
};

#endif	/* COMPONENTCLASSREPOSITORY_H */

