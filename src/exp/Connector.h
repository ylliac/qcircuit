/* 
 * File:   Connector.h
 * Author: acailly
 *
 * Created on 3 mars 2014, 18:21
 */

#ifndef CONNECTOR_H
#define	CONNECTOR_H

#include "core/FBPComponent.h"

class Connector : public FBPComponent
{
    Q_OBJECT    
public:
    Connector();
    virtual ~Connector();
        
public slots:
    void in(QVariant v = QVariant(true));
    
signals:
    void out(QVariant);
    
protected:
    virtual void execute();

};

#endif	/* CONNECTOR_H */

