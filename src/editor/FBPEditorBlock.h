/* 
 * File:   FBPEditorBlock.h
 * Author: acailly
 *
 * Created on 24 février 2014, 18:29
 */

#ifndef FBPEDITORBLOCK_H
#define	FBPEDITORBLOCK_H

#include <QtCore/QObject>

class FBPEditorBlock : public QObject {
public:
    FBPEditorBlock();
    virtual ~FBPEditorBlock();
    
private:
    Q_DISABLE_COPY(FBPEditorBlock);
};

#endif	/* FBPEDITORBLOCK_H */

