/* 
 * File:   IIP.h
 * Author: acailly
 *
 * Created on 3 février 2014, 14:15
 */

#ifndef IIP_H
#define	IIP_H

#include "core/FBPComponent.h"

class IIP : public FBPComponent{
public:
    IIP();
    virtual ~IIP();
    
protected:
    virtual void execute();
};

#endif	/* IIP_H */

