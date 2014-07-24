/* 
 * File:   FBPNetwork.h
 * Author: acailly
 *
 * Created on 17 février 2014, 12:07
 */

#ifndef FBPNETWORK_H
#define	FBPNETWORK_H

#include <QtCore/QMutex>
#include <QtCore/QWaitCondition>

#include "FBPComponent.h"
#include "Counter.h"
#include "FBPComponentListener.h"

class FBPNetwork : public FBPComponent, public FBPComponentListener {
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
    
    //TODO ACY A implémenter
//    bool connectSubIn(QString inPortName, FBPComponent* target, QString targetPortName);
//    bool connectSubOut(FBPComponent* source, QString sourcePortName, QString outPortName);
//    bool connectSubInToOut(QString inPortName, QString outPortName);
    
    //MONITORING
    
    virtual void componentActivated(FBPComponent* component);
    virtual void componentFinished(FBPComponent* component);
            
protected:
    virtual void execute();
    virtual void define();
    
private:
    void initiate();
    void waitForAll();
    
    QMap<QString, FBPComponent*> componentMap;
    Counter* activeComponentCounter;
    bool isDefined;
    
    QMutex mutex;
    QWaitCondition monitor;

};

#endif	/* FBPNETWORK_H */

