/* 
 * File:   BlockDescription.h
 * Author: acailly
 *
 * Created on 4 juin 2014, 18:34
 */

#ifndef COMPONENTCLASSDESCRIPTOR_H
#define	COMPONENTCLASSDESCRIPTOR_H

#include <QtCore/QObject>
#include <QtCore/QMap>
#include <QtCore/QList>

#include "core/FBPComponent.h"

class ComponentClassDescriptor : public QObject {
    Q_OBJECT
    
public:
    ComponentClassDescriptor();
    virtual ~ComponentClassDescriptor();
        
    QString getClassName() const;
    void setClassName(QString value);
    
    QString getDescription() const;
    void setDescription(QString value);
    
    QList<QString> getInPorts() const;
    QString getInPortDescription(QString portName) const;
    void addInPort(QString portName, QString portDescription);
    
    QList<QString> getOutPorts() const;
    QString getOutPortDescription(QString portName) const;
    void addOutPort(QString portName, QString portDescription);
    
    virtual FBPComponent* newComponent() const;
    
private:
    QString m_ClassName;
    QString m_Description;
    QMap<QString, QString> m_InPorts;
    QMap<QString, QString> m_OutPorts;
};

#endif	/* COMPONENTCLASSDESCRIPTOR_H */

