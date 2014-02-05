/* 
 * File:   QComponent.cpp
 * Author: acailly
 * 
 * Created on 4 février 2014, 11:25
 */

#include "QComponent.h"

#include <iostream>

#include <QtCore/QMetaObject>
#include <QtCore/QMetaClassInfo>

const QString QComponent::METADATA_IN = "IN";
const QString QComponent::METADATA_OUT = "OUT";

QComponent::QComponent()
{
}

QComponent::~QComponent()
{
}

void QComponent::createInOutFromMetadata()
{        
    int metadataCount = metaObject()->classInfoCount();
    for (int metadataIndex = 0; metadataIndex < metadataCount; metadataIndex++)
    {
        QMetaClassInfo metadata = metaObject()->classInfo(metadataIndex);
        if(QString(metadata.value()).compare(METADATA_IN, Qt::CaseInsensitive) == 0)
        {
            std::string portName = metadata.name();
            AddInput_(portName);
        }
        else if(QString(metadata.value()).compare(METADATA_OUT, Qt::CaseInsensitive) == 0)
        {
            std::string portName = metadata.name();
            AddOutput_(portName);  
        }
    }
}

