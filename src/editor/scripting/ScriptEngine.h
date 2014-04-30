/* 
 * File:   ScriptEngine.h
 * Author: acailly
 *
 * Created on 30 avril 2014, 17:02
 */

#ifndef SCRIPTENGINE_H
#define	SCRIPTENGINE_H

#include <QtCore/QObject>
#include <QtCore/QList>

class FBPEditor;
class FBPEditorAction;
class ScriptCommand;

class ScriptEngine : public QObject {
    Q_OBJECT
    
public:
    ScriptEngine(FBPEditor* editor);
    virtual ~ScriptEngine();
    
    void addScriptCommand(QString input, FBPEditorAction* action);
    
    bool runScriptCommand(QString input);
    
private:
    FBPEditor* m_Editor;
    QList<ScriptCommand*> m_Commands;
    
    QList<QString> m_History;
};

#endif	/* SCRIPTENGINE_H */

