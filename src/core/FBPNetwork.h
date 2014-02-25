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
    
    bool connectFromSignal(const QObject* sender, const char* signal, FBPComponent* target, QString inPortName);
    
    void go();
    
protected:
    virtual void execute();
    virtual void define();
    
private:
    void initiate();
    void waitForAll();
    
    QMap<QString, FBPComponent*> componentMap;
    Counter* activeComponentCounter;

};

#endif	/* FBPNETWORK_H */

