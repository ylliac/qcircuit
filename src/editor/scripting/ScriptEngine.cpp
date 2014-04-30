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

ScriptEngine::ScriptEngine(FBPEditor* editor) :
m_Editor(editor)
{
}

ScriptEngine::~ScriptEngine()
{
}

void ScriptEngine::addScriptCommand(QString input, FBPEditorAction* action)
{
    ScriptCommand* newScriptCommand = new ScriptCommand(input);
    m_Commands.append(newScriptCommand);

    QObject::connect(newScriptCommand, SIGNAL(exec(QString,QString,QString,QString,QString)), action, SLOT(execute(QString,QString,QString,QString,QString)));    
}

bool ScriptEngine::runScriptCommand(QString input)
{
    bool result = false;

    //Save the input in the history
    m_History.append(input);
    
    //Run the associated command
    foreach(ScriptCommand* command, m_Commands){
        if(command->apply(input))
        {
            result = true;
            break;
        }
    }
    
    return result;
}

