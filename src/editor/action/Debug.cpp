/* 
 * File:   Debug.cpp
 * Author: acailly
 * 
 * Created on 4 juin 2014, 17:20
 */

#include "Debug.h"

#include "editor/FBPEditor.h"

#include "../core/FBPComponent.h"
#include "../core/FBPNetwork.h"

#include "../loader/NetworkLoaderFromFBP.h"

#include "../common/Timer.h"
#include "../common/UDPEmitter.h"
#include "../common/UDPReceiver.h"
#include "../common/Console.h"

#include "descriptor/ComponentClassRepository.h"
#include "descriptor/QtComponentClassDescriptor.h"

#include <QtCore/QTemporaryFile>
#include <QtCore/QFileInfo>

Debug::Debug(FBPEditor* editor) :
FBPEditorAction(editor)
{
}

Debug::~Debug()
{
}

void Debug::execute(QString name, QString className, QString, QString, QString)
{
    //Create a temporary file
    QTemporaryFile file;
    //Open the temporary file to generate the file Name
    if (file.open())
    {
        file.close();
    }
    
    //Export the diagram in the temporary file    
    getEditor()->runScriptCommand(
            QString("Export diagram in file %1")
            .arg(QFileInfo(file).absoluteFilePath())
            );
    
    //Create a network and load the temporary file
    NetworkLoaderFromFBP loader;
    FBPNetwork* network = loader.loadFromFile(QFileInfo(file).absoluteFilePath(), getEditor()->getComponentClassRepository());    
    network->setParent(getEditor());
    network->activate();
    network->wait();
}

