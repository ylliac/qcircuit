/* 
 * File:   ScriptEngine.cpp
 * Author: acailly
 * 
 * Created on 30 avril 2014, 17:02
 */

#include "ScriptEngine.h"

#include "ScriptCommand.h"
#include "editor/FBPEditor.h"
#include "editor/action/FBPEditorAction.h"

#include <QtCore/QRegExp>
#include <QtCore/QFile>
#include <QtCore/QTextStream>
#include <QtGui/QMessageBox>

#include <iostream>

ScriptEngine::ScriptEngine(FBPEditor* editor) :
m_Editor(editor),
m_CurrentActionLevel(0)
{
}

ScriptEngine::~ScriptEngine()
{
}

void ScriptEngine::registerAction(QString actionName, FBPEditorAction* action)
{
    m_Actions.insert(actionName, action);
}

FBPEditorAction* ScriptEngine::findAction(QString actionName)
{
    return m_Actions.value(actionName);
}

void ScriptEngine::registerScriptCommand(QString input, QString actionName)
{
    FBPEditorAction* action = findAction(actionName);
    if(action != NULL)
    {    
        ScriptCommand* newScriptCommand = new ScriptCommand(input);
        m_Commands.append(newScriptCommand);

        QObject::connect(newScriptCommand, SIGNAL(exec(QString,QString,QString,QString,QString)), action, SLOT(execute(QString,QString,QString,QString,QString)));    
    }
    else
    {
        std::cerr << "Unable to find the action " << actionName.toStdString() << std::endl;
    }
}

bool ScriptEngine::runScriptCommand(QString input)
{       
    bool result = false;
    
    //Save the input in the history
    m_History.append(QPair<int, QString>(m_CurrentActionLevel, input));
    
    //Log the command
    QString logPrefix;
    for(int i=0; i < m_CurrentActionLevel; i++)
    {
        logPrefix.append('-');
    }
    if(m_CurrentActionLevel > 0)
    {
        logPrefix.append(' ');            
    }
    std::cout << logPrefix.toStdString() << "COMMAND " << input.toStdString() << std::endl;
    
    //Increase the current action level
    m_CurrentActionLevel++;
    
    //Run the associated command
    foreach(ScriptCommand* command, m_Commands)
    {
        if(command->apply(input))
        {
            result = true;            
            break;
        }
    }
    
    //Decrease the current action level
    m_CurrentActionLevel--;
    
    //Log if error  
    if(!result)
    {
        std::cerr << "COMMAND NOT FOUND: " << input.toStdString() << std::endl;
    }
    
    return result;
}

void ScriptEngine::loadAssociationFile(QString filePath)
{
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox::critical(m_Editor, tr("Unable to open file"),
                file.errorString());
        return;
    }
    else
    {
        QRegExp actionExp("^\\s*ACTION\\s*([^\\s]+)\\s*$");
        QRegExp commandExp("^\\s*COMMAND\\s*([^\\s].*[^\\s])\\s*$");
        
        QString currentAction = "";
        
        QTextStream in(&file);
        while(!in.atEnd())
        {
            QString line = in.readLine();
            
            if (actionExp.exactMatch(line))
            {
                currentAction = actionExp.cap(1);
            }
            else if(commandExp.exactMatch(line))
            {
                QString command = commandExp.cap(1);
                registerScriptCommand(command, currentAction);
            }
        }
        file.close();
    }
}

