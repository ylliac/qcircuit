/* 
 * File:   QtComponentClassDescriptor.h
 * Author: acailly
 *
 * Created on 4 juin 2014, 19:02
 */

#ifndef QTCOMPONENTCLASSDESCRIPTOR_H
#define	QTCOMPONENTCLASSDESCRIPTOR_H

#include "ComponentClassDescriptor.h"

#include <QtCore/QMetaObject>

class QtComponentClassDescriptor : public ComponentClassDescriptor {
    Q_OBJECT
    
public:
    QtComponentClassDescriptor(QMetaObject metaObject);
    virtual ~QtComponentClassDescriptor();
    
    virtual FBPComponent* newComponent() const;
    
private:
    void initialize();
    
    QMetaObject m_MetaObject;
};

#endif	/* QTCOMPONENTCLASSDESCRIPTOR_H */

