/* 
 * File:   FBPSubNetwork.h
 * Author: acailly
 *
 * Created on 19 février 2014, 14:04
 */

#ifndef FBPSUBNETWORK_H
#define	FBPSUBNETWORK_H

#include "FBPNetwork.h"

class FBPSubNetwork : FBPNetwork
{
    Q_OBJECT
    
public:
    FBPSubNetwork(QObject* parent = NULL);
    virtual ~FBPSubNetwork();
    
protected:
    virtual void execute();

};

#endif	/* FBPSUBNETWORK_H */

