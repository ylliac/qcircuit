/* 
 * File:   Test.h
 * Author: acailly
 *
 * Created on 14 février 2014, 11:20
 */

#ifndef TEST_H
#define	TEST_H

#include "../core/FBPComponent.h"

class Test : public FBPComponent
{
    Q_OBJECT
    
public:
    Test();
    virtual ~Test();
    
protected:
    virtual void execute();
};

#endif	/* TEST_H */

