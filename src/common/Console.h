/* 
 * File:   Console.h
 * Author: acailly
 *
 * Created on 4 février 2014, 11:46
 */

#ifndef CONSOLE_H
#define	CONSOLE_H

#include "../core/FBPComponent.h"

class Console : public FBPComponent {
    Q_OBJECT
    
public:
    Q_INVOKABLE Console();
    virtual ~Console();
        
protected:
    virtual void execute();

};

#endif	/* CONSOLE_H */

