/* 
 * File:   FBPEditorBlock.h
 * Author: acailly
 *
 * Created on 24 février 2014, 18:29
 */

#ifndef FBPEDITORBLOCK_H
#define	FBPEDITORBLOCK_H

#include <QtCore/QObject>

class FBPEditor;

class FBPEditorBlock : public QObject {
public:
    FBPEditorBlock();
    virtual ~FBPEditorBlock();
    
    bool isAttached();
    void attach(FBPEditor* editor);
    void detach();
    FBPEditor* getEditor();
    
protected:
    virtual void attachImpl()=0;
    virtual void detachImpl()=0;
    
private:
    Q_DISABLE_COPY(FBPEditorBlock);
    
    FBPEditor* m_Editor;
};

#endif	/* FBPEDITORBLOCK_H */

