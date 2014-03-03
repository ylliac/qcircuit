/* 
 * File:   FBPNetwork.h
 * Author: acailly
 *
 * Created on 17 février 2014, 12:07
 */

#ifndef FBPNETWORK_H
#define	FBPNETWORK_H

#include "FBPComponent.h"
#include "Counter.h"

class FBPNetwork : public FBPComponent {
    Q_OBJECT
    
public:
    FBPNetwork(QObject* parent = NULL);
    virtual ~FBPNetwork();
    
    //COMPONENT
    
    FBPComponent* getComponent(QString name);
    void addComponent(FBPComponent* component, QString name);
    
    //IIP
    
    bool initialize(QVariant value, FBPComponent* target, QString inPortName);
    bool initialize(QVariant value, QString target, QString inPortName);
    bool initialize(QVariant value, QString target);
    
    //CONNECTION
    
    bool connect(FBPComponent* source, QString outPortName, FBPComponent* target, QString inPortName);
    bool connect(QString source, QString outPortName, QString target, QString inPortName);
    bool connect(QString source, QString target);
    
    bool connectSubIn(QString inPortName, FBPComponent* target, QString targetPortName);
    bool connectSubOut(FBPComponent* source, QString sourcePortName, QString outPortName);
    bool connectSubInToOut(QString inPortName, QString outPortName);
    
    bool connectFromSignal(const QObject* sender, const char* signal, QString inPortName);
    bool connectToSlot(QString outPortName, const QObject* target, const char* slot);
            
protected:
    virtual void execute();
    virtual void define();
    
private:
    void initiate();
    void waitForAll();
    
    QMap<QString, FBPComponent*> componentMap;
    Counter* activeComponentCounter;
    bool isDefined;

};

#endif	/* FBPNETWORK_H */

