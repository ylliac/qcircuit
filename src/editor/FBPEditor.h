/* 
 * File:   FBPEditor.h
 * Author: acailly
 *
 * Created on 24 février 2014, 17:48
 */

#ifndef _FBPEDITOR_H
#define	_FBPEDITOR_H

#include <QtGui/QMainWindow>

#include <QtCore/QMap>

#include "scripting/ScriptEngine.h"

class FBPEditorBlock;

namespace Ui {
    class FBPEditor;
}

class EditorScene;

class FBPEditor : public QMainWindow {
    Q_OBJECT
    
public:
    FBPEditor(QWidget* parent = 0, Qt::WindowFlags windowFlag = 0);
    virtual ~FBPEditor();
    
    EditorScene* getScene();
    ScriptEngine* getScriptEngine();
    
    bool runScriptCommand(QString input);
    
private:
    void initialize();
    
    Ui::FBPEditor* ui;
    EditorScene* m_Scene;
    ScriptEngine* m_ScriptEngine;
};

#endif	/* _FBPEDITOR_H */
