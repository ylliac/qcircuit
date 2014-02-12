/* 
 * File:   CircuitLoaderFromFBP.cpp
 * Author: acailly
 * 
 * Created on 7 février 2014, 18:37
 */

#include "CircuitLoaderFromFBP.h"

#include "../core/QCircuit.h"
#include "core/QComponent.h"

#include <iostream>

#include <QtCore/QRegExp>
#include <QtCore/QTextStream>
#include <QtCore/QFile>
#include <QtCore/QFileInfo>
#include <QtCore/QStringList>

CircuitLoaderFromFBP::CircuitLoaderFromFBP()
{
}

CircuitLoaderFromFBP::~CircuitLoaderFromFBP()
{
}

QCircuit* CircuitLoaderFromFBP::loadFromFile(QString filePath) const
{
    QCircuit* result = new QCircuit();

    //TODO ACY 
    ////Example : ComponentName ( ComponentClass )
    //QRegExp componentDeclarationExp("^\\s*([^\\s]+)\\s*\\(\\s*([^\\s]+)\\s*\\)\\s*$");
    //Example : ComponentName _ComponentClass_ ( null )
    QRegExp componentDeclarationExp("^\\s*([^\\s]+)\\s*_\\s*([^\\s]+)\\s*_.*$");

    //TODO ACY
    ////Example : SourceComponentName SourceComponentOutput -> TargetComponentInput TargetComponentName
    //QRegExp relationDeclarationExp("^\\s*([^\\s]+)\\s+([^\\s]+)\\s*-+>\\s*([^\\s]+)\\s*([^\\s]+)\\s*$");
    //Example : SourceComponentName _SourceComponentClass_ SourceComponentOutput -> TargetComponentInput TargetComponentName _TargetComponentClass_
    QRegExp relationDeclarationExp("^\\s*([^\\s]+).*([^\\s]+)\\s*-+>\\s*([^\\s]+)\\s*([^\\s]+).*$");

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
            bool check = result->ConnectOutToIn(source, target);
            if(!check)
            {
                std::cout << "ERROR - Can't add connection: " << source.toStdString() << " --> " << target.toStdString() << std::endl;                        
            }
        }
        //------------------------------------------------------------------
        // DECLARATION 
        //------------------------------------------------------------------
        else if (componentDeclarationExp.exactMatch(instruction))
        {
            QString componentName = componentDeclarationExp.cap(1);
            QString componentClass = componentDeclarationExp.cap(2);

            if(m_ComponentClasses.contains(componentClass))
            {
                const QMetaObject metaObject = m_ComponentClasses.value(componentClass);
                QComponent* newComponent = qobject_cast<QComponent*>(metaObject.newInstance());
                bool check = result->AddComponent(newComponent, componentName.toStdString());
                if(!check)
                {
                    std::cout << "ERROR - Can't add component: " << componentName.toStdString() << std::endl;                        
                }
            }
            else{
                std::cout << "ERROR - Component class not found: " << componentClass.toStdString() << std::endl;                        
            }
        }
    }

    return result;
}

void CircuitLoaderFromFBP::addComponentClass(QString className, QMetaObject metaObject)
{
    m_ComponentClasses.insert(className, metaObject);
}
