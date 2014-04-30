/* 
 * File:   FBPEditor.h
 * Author: acailly
 *
 * Created on 24 février 2014, 17:48
 */

#ifndef _FBPEDITOR_H
#define	_FBPEDITOR_H

#include <QtGui/QMainWindow>
#include <QtGui/QGraphicsView>

#include <QtCore/QMap>

#include "titlebar/WindowTitleBar.h"
#include "scripting/ScriptEngine.h"
#include "notifications/NotificationPanel.h"

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

    QGraphicsView* getGraphicsView();
    EditorScene* getScene();
    ScriptEngine* getScriptEngine();
    NotificationPanel* getNotificationPanel();

    bool runScriptCommand(QString input);

    void setWindowTitle(const QString &title);

signals:
    void windowTitleChanged();

protected:
    void paintEvent(QPaintEvent *event);

private:
    void initialize();

    Ui::FBPEditor* ui;
    WindowTitleBar* m_TitleBar;

    EditorScene* m_Scene;
    ScriptEngine* m_ScriptEngine;
    NotificationPanel* m_NotificationPanel;
};

#endif	/* _FBPEDITOR_H */
