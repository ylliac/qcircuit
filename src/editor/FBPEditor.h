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

#include "FBPEditorBlock.h"

class FBPEditorBlock;
class FBPNetwork;

namespace Ui {
    class FBPEditor;
}

class QGraphicsScene;

class FBPEditor : public QMainWindow {
    Q_OBJECT
    
public:
    FBPEditor(QWidget* parent = 0, Qt::WindowFlags windowFlag = 0);
    virtual ~FBPEditor();
    
    void addBlock(QString idName, FBPEditorBlock* block);
    void removeBlock(QString idName);
    void removeBlock(FBPEditorBlock* block);
    FBPEditorBlock* getBlock(QString idName);
    
    QGraphicsScene* getScene();
    FBPNetwork* getNetwork();
    
private:
    void initialize();
    
    Ui::FBPEditor* ui;
    QGraphicsScene* m_GraphicsScene;
    
    QMap<QString, FBPEditorBlock*> m_Blocks;
    FBPNetwork* m_Network;
};

#endif	/* _FBPEDITOR_H */
