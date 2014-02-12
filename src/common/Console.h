/* 
 * File:   Console.h
 * Author: acailly
 *
 * Created on 4 février 2014, 11:46
 */

#ifndef CONSOLE_H
#define	CONSOLE_H

#include "../core/QComponent.h"

class Console : public QComponent {
    Q_OBJECT
    Q_CLASSINFO("MESSAGE", "IN")
    
public:
    Q_INVOKABLE Console();
    virtual ~Console();
        
protected:
    virtual void Process_(DspSignalBus& inputs, DspSignalBus& outputs);

};

#endif	/* CONSOLE_H */

