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
#include <QtCore/QMap>
#include <QtCore/QPair>

class FBPEditor;
class FBPEditorAction;
class ScriptCommand;

class ScriptEngine : public QObject {
    Q_OBJECT
    
public:
    ScriptEngine(FBPEditor* editor);
    virtual ~ScriptEngine();
    
    void registerAction(QString actionName, FBPEditorAction* action);
    void registerScriptCommand(QString input, QString actionName);
    
    bool runScriptCommand(QString input);
    
    void loadAssociationFile(QString filePath);
    
private:
    FBPEditorAction* findAction(QString actionName);
    
    FBPEditor* m_Editor;
    QMap<QString, FBPEditorAction*> m_Actions;
    QList<ScriptCommand*> m_Commands;
    
    QList<QPair<int, QString> > m_History;
    
    int m_CurrentActionLevel;
};

#endif	/* SCRIPTENGINE_H */

