/* 
 * File:   FBPEditorAction.h
 * Author: acailly
 *
 * Created on 3 mars 2014, 18:32
 */

#ifndef FBPEDITORACTION_H
#define	FBPEDITORACTION_H

#include <QtCore/QObject>

#include "editor/FBPEditor.h"

class FBPEditorAction : public QObject {
    Q_OBJECT
    
    //TODO ACY Idée :
    //Les actions sont le point d'entrée de l'utilisateur. 
    //Il pourraient être aussi le point d'entrée d'un mode console, d'un test ou d'un moteur de script.
    //Ce qui serait pas mal c'est de mettre en place un mécanisme qui permette de faire le mapping entre l'action et un texte.
    //Le mapping texte -> action permettrait de :
    //   - faire du BDD
    //   - générer automatiquement des actions à partir d'un script
    //Le mapping action -> texte permettrait de :
    //   - Logger automatiquement les actions
    //   - Reproduire facilement l'éxécution d'un logiciel à partir de son log
    //   - Enregistrer un script (ou macro) en live dans le logiciel
    
public:
    FBPEditorAction(FBPEditor* editor);
    virtual ~FBPEditorAction();
    
    FBPEditor* getEditor();
    
public slots:
    //TODO ACY Au lieu de retourner void retourner un objet permettant de stocker des messages d'erreur
    virtual void execute(QString arg1 = 0, QString arg2 = 0, QString arg3 = 0, QString arg4 = 0, QString arg5 = 0) = 0;
    
private:
    FBPEditor* m_Editor;
};

#endif	/* FBPEDITORACTION_H */

