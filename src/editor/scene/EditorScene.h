/* 
 * File:   EditorScene.h
 * Author: acailly
 *
 * Created on 5 mars 2014, 17:15
 */

#ifndef EDITORSCENE_H
#define	EDITORSCENE_H

#include <QtGui/QGraphicsScene>

class EditorScene : public QGraphicsScene{
    Q_OBJECT
    
public:
    EditorScene(QObject *parent = 0);
    virtual ~EditorScene();
};

#endif	/* EDITORSCENE_H */

