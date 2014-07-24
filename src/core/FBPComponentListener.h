/* 
 * File:   FBPComponentListener.h
 * Author: acailly
 *
 * Created on 24 juillet 2014, 16:55
 */

#ifndef FBPCOMPONENTLISTENER_H
#define	FBPCOMPONENTLISTENER_H

#include "FBPComponent.h"

class FBPComponentListener {
public:
    virtual ~FBPComponentListener(){}
    
    virtual void componentActivated(FBPComponent* component) = 0;
    virtual void componentFinished(FBPComponent* component) = 0;

};

#endif	/* FBPCOMPONENTLISTENER_H */

