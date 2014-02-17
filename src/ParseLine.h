/* 
 * File:   ParseLine.h
 * Author: acailly
 *
 * Created on 29 janvier 2014, 17:40
 */

#ifndef PARSELINE_H
#define	PARSELINE_H

#include "core/FBPComponent.h"

class ParseLine : public FBPComponent{
public:
    ParseLine();
    virtual ~ParseLine();
    
protected:
    virtual void execute();

};

#endif	/* PARSELINE_H */

