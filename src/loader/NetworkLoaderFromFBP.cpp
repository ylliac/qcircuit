/* 
 * File:   NetworkLoaderFromFBP.cpp
 * Author: acailly
 * 
 * Created on 17 février 2014, 14:50
 */

#include "NetworkLoaderFromFBP.h"

#include "core/FBPComponent.h"
#include "core/FBPNetwork.h"
#include "common/Script.h"
#include "descriptor/ComponentClassDescriptor.h"
#include "descriptor/ComponentClassRepository.h"

#include <iostream>

#include <QtCore/QRegExp>
#include <QtCore/QTextStream>
#include <QtCore/QFile>
#include <QtCore/QFileInfo>
#include <QtCore/QDir>
#include <QtCore/QStringList>

NetworkLoaderFromFBP::NetworkLoaderFromFBP()
{
}

NetworkLoaderFromFBP::~NetworkLoaderFromFBP()
{
}

FBPNetwork* NetworkLoaderFromFBP::loadFromFile(QString networkFilePath, ComponentClassRepository* repository) const
{
    FBPNetwork* result = new FBPNetwork();

    //Example : ComponentName ( ComponentClass )
    QRegExp componentDeclarationExp("^\\s*([^\\s]+)\\s*\\(\\s*([^\\s]+)\\s*\\)\\s*$");

    //Example : SourceComponentName SourceComponentOutput -> TargetComponentInput TargetComponentName
    QRegExp relationDeclarationExp("^\\s*([^\\s]+)\\s+([^\\s]+)\\s*-+>\\s*([^\\s]+)\\s*([^\\s]+)\\s*$");               

    //Example : "IIP" -> TargetComponentInput TargetComponentName
    QRegExp iipDeclarationExp("^\\s*\"(.+)\"\\s*-+>\\s*([^\\s]+)\\s*([^\\s]+)\\s*$");
    
    //Example : script:file.script
    QRegExp scriptExp("^\\s*script:\\s*(.+)\\s*$");

    QString content;
    QFile networkFile(networkFilePath);    
    if (networkFile.open(QIODevice::ReadOnly)) {
        QTextStream in(&networkFile);
        content = in.readAll();
        networkFile.close();
    }
        
    QStringList instructions = content.split(QRegExp("[\r\n]"),QString::SkipEmptyParts);
    foreach(QString instruction, instructions)
    {               
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
        else if (iipDeclarationExp.exactMatch(instruction))
        {
            QString iipContent = iipDeclarationExp.cap(1);
            QString targetComponentInput = iipDeclarationExp.cap(2);
            QString targetComponentName = iipDeclarationExp.cap(3);

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

            //Special case for scripts
            if(scriptExp.exactMatch(componentClass))
            {
                QString scriptFilePath = scriptExp.cap(1);
                if(!QFileInfo(scriptFilePath).exists())
                {
                    scriptFilePath = QFileInfo(networkFilePath).absoluteDir().filePath(scriptFilePath);
                }
                QFile scriptFile(scriptFilePath);
                
                if(scriptFile.exists())
                {
                    QString script;
                    if (scriptFile.open(QIODevice::ReadOnly)) {
                        QTextStream in(&scriptFile);
                        script = in.readAll();
                        networkFile.close();
                    }
                    
                    FBPComponent* newComponent = new Script(script);
                    if(newComponent != NULL)
                    {
                        result->addComponent(newComponent, componentName);
                        newComponent->setObjectName(QString("%1 (%2)").arg(componentName).arg(componentClass));
                    }
                }
                else
                {
                    std::cerr << "ERROR - Script file not found: " << QFileInfo(scriptFile).absoluteFilePath().toStdString() << std::endl;                        
                }
            }
            else
            {
                const ComponentClassDescriptor* descriptor = repository->findComponentClass(componentClass);
                if(descriptor != NULL)
                {
                    FBPComponent* newComponent = descriptor->newComponent();
                    if(newComponent != NULL)
                    {
                        result->addComponent(newComponent, componentName);
                        newComponent->setObjectName(QString("%1 (%2)").arg(componentName).arg(componentClass));
                    }
                }
                else{
                    std::cerr << "ERROR - Component class not found: " << componentClass.toStdString() << std::endl;                        
                }
            }
        }
        //------------------------------------------------------------------
        // IGNORED 
        //------------------------------------------------------------------
        else
        {
            std::cerr << "WARNING - Ignored instruction: [" << instruction.toStdString() << "]." << std::endl;                        
        }
    }

    return result;
}

