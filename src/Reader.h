/* 
 * File:   Reader.h
 * Author: acailly
 *
 * Created on 3 février 2014, 12:17
 */

#ifndef READER_H
#define	READER_H

#include "core/FBPComponent.h"

class Reader : public FBPComponent{
public:
    Reader();
    virtual ~Reader();
    
protected:
    virtual void execute();

};

#endif	/* READER_H */

