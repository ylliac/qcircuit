/* 
 * File:   ExportDiagram.h
 * Author: HOME
 *
 * Created on 17 mai 2014, 12:02
 */

#ifndef EXPORTDIAGRAM_H
#define	EXPORTDIAGRAM_H

#include "FBPEditorAction.h"

class ExportDiagram : public FBPEditorAction {
    Q_OBJECT
    
public:
    ExportDiagram(FBPEditor* editor);
    virtual ~ExportDiagram();
    
public slots:
    virtual void execute(QString arg1 = 0, QString arg2 = 0, QString arg3 = 0, QString arg4 = 0, QString arg5 = 0);

};

#endif	/* EXPORTDIAGRAM_H */

