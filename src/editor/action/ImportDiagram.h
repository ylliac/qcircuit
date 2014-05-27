/* 
 * File:   ImportDiagram.h
 * Author: acailly
 *
 * Created on 27 mai 2014, 10:30
 */

#ifndef IMPORTDIAGRAM_H
#define	IMPORTDIAGRAM_H

#include "FBPEditorAction.h"

class ImportDiagram : public FBPEditorAction {
    Q_OBJECT
    
public:
    ImportDiagram(FBPEditor* editor);
    virtual ~ImportDiagram();
    
public slots:
    virtual void execute(QString arg1 = 0, QString arg2 = 0, QString arg3 = 0, QString arg4 = 0, QString arg5 = 0);

};

#endif	/* IMPORTDIAGRAM_H */

