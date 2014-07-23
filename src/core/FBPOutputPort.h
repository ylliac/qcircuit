/* 
 * File:   FBPOutputPort.h
 * Author: acailly
 *
 * Created on 14 février 2014, 18:19
 */

#ifndef FBPOUTPUTPORT_H
#define	FBPOUTPUTPORT_H

#include <QtCore/QVariant>

#include "FBPPort.h"

class FBPOutputPort : public FBPPort{
    Q_OBJECT
    
public:
    FBPOutputPort(QString name);
    virtual ~FBPOutputPort();
    
public slots:
    void send(QVariant value);
    void close();
    
signals:
    void sent(QVariant value);
};

#endif	/* FBPOUTPUTPORT_H */

