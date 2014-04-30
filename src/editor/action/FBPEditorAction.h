/* 
 * File:   FBPEditorAction.h
 * Author: acailly
 *
 * Created on 3 mars 2014, 18:32
 */

#ifndef FBPEDITORACTION_H
#define	FBPEDITORACTION_H

#include <QtCore/QObject>

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
    FBPEditorAction();
    virtual ~FBPEditorAction();
    
public slots:
    virtual void execute() = 0;
};

#endif	/* FBPEDITORACTION_H */

