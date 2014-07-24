/* 
 * File:   NetworkLoaderFromFBP.cpp
 * Author: acailly
 * 
 * Created on 17 février 2014, 14:50
 */

#include "NetworkLoaderFromFBP.h"

#include "../core/FBPComponent.h"
#include "../core/FBPNetwork.h"
#include "descriptor/ComponentClassDescriptor.h"
#include "descriptor/ComponentClassRepository.h"

#include <iostream>

#include <QtCore/QRegExp>
#include <QtCore/QTextStream>
#include <QtCore/QFile>
#include <QtCore/QFileInfo>
#include <QtCore/QStringList>

NetworkLoaderFromFBP::NetworkLoaderFromFBP()
{
}

NetworkLoaderFromFBP::~NetworkLoaderFromFBP()
{
}

FBPNetwork* NetworkLoaderFromFBP::loadFromFile(QString filePath, ComponentClassRepository* repository) const
{
    FBPNetwork* result = new FBPNetwork();

    //Example : ComponentName ( ComponentClass )
    QRegExp componentDeclarationExp("^\\s*([^\\s]+)\\s*\\(\\s*([^\\s]+)\\s*\\)\\s*$");

    //Example : SourceComponentName SourceComponentOutput -> TargetComponentInput TargetComponentName
    QRegExp relationDeclarationExp("^\\s*([^\\s]+)\\s+([^\\s]+)\\s*-+>\\s*([^\\s]+)\\s*([^\\s]+)\\s*$");

    //Example : "IIP" -> TargetComponentInput TargetComponentName
    QRegExp IIPDeclarationExp("^\\s*\"([^\\s]+)\"\\s*-+>\\s*([^\\s]+)\\s*([^\\s]+)\\s*$");

    QString content;
    QFile file(filePath);    
    if (file.open(QIODevice::ReadOnly)) {
        QTextStream in(&file);
        content = in.readAll();
        file.close();
    }
        
    QStringList instructions = content.split(",");
    foreach(QString instruction, instructions)
    {
        instruction = instruction.replace("\n", " ");
                
        //------------------------------------------------------------------
        // CONNEXION 
        //------------------------------------------------------------------        
        if (relationDeclarationExp.exactMatch(instruction))
        {
            QString sourceComponentName = relationDeclarationExp.cap(1);
            QString sourceComponentOutput = relationDeclarationExp.cap(2);
            QString targetComponentInput = relationDeclarationExp.cap(3);
            QString targetComponentName = relationDeclarationExp.cap(4);

            QString source = QString("%1.%2").arg(sourceComponentName).arg(sourceComponentOutput);
            QString target = QString("%1.%2").arg(targetComponentName).arg(targetComponentInput);
            bool check = result->connect(source, target);
            if(!check)
            {
                std::cerr << "ERROR - Can't add connection: " << source.toStdString() << " --> " << target.toStdString() << std::endl;                        
            }
        }
        //------------------------------------------------------------------
        // IIP
        //------------------------------------------------------------------        
        if (IIPDeclarationExp.exactMatch(instruction))
        {
            QString iipContent = IIPDeclarationExp.cap(1);
            QString targetComponentInput = IIPDeclarationExp.cap(2);
            QString targetComponentName = IIPDeclarationExp.cap(3);

            QVariant iip = QVariant::fromValue(iipContent);
                        
            QString target = QString("%1.%2").arg(targetComponentName).arg(targetComponentInput);
            bool check = result->initialize(iip, target);
            if(!check)
            {
                std::cerr << "ERROR - Can't add iip: " << "IIP --> " << target.toStdString() << std::endl;                        
            }
        }
        //------------------------------------------------------------------
        // DECLARATION 
        //------------------------------------------------------------------
        else if (componentDeclarationExp.exactMatch(instruction))
        {
            QString componentName = componentDeclarationExp.cap(1);
            QString componentClass = componentDeclarationExp.cap(2);

            const ComponentClassDescriptor* descriptor = repository->findComponentClass(componentClass);
            if(descriptor != NULL)
            {
                FBPComponent* newComponent = descriptor->newComponent();
                if(newComponent != NULL)
                {
                    result->addComponent(newComponent, componentName);
                }
            }
            else{
                std::cerr << "ERROR - Component class not found: " << componentClass.toStdString() << std::endl;                        
            }
        }
    }

    return result;
}

