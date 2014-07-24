/* 
 * File:   FBPOutputPort.h
 * Author: acailly
 *
 * Created on 14 février 2014, 18:19
 */

#ifndef FBPOUTPUTPORT_H
#define	FBPOUTPUTPORT_H

#include <QtCore/QVariant>
#include <QtCore/QSet>

#include "FBPPort.h"
#include "FBPInputPort.h"

class FBPOutputPort : public FBPPort{
    Q_OBJECT
    
public:
    FBPOutputPort(QString name);
    virtual ~FBPOutputPort();
    
    void connect(FBPInputPort* receiver);
    void disconnect(FBPInputPort* receiver);
    
    void send(QVariant value);
    void close();

private:
    QSet<FBPInputPort*> receivers; 
};

#endif	/* FBPOUTPUTPORT_H */

