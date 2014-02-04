/* 
 * File:   StringCondition.h
 * Author: acailly
 *
 * Created on 29 janvier 2014, 17:49
 */

#ifndef STRINGCONDITION_H
#define	STRINGCONDITION_H

#include <dspatch/DspComponent.h>
#include <dspatch/DspSignalBus.h>

#include <QtCore/QString>

class StringCondition : public DspComponent{
public:
    StringCondition(QString expectedString);
    virtual ~StringCondition();
    
protected:
    virtual void Process_(DspSignalBus& inputs, DspSignalBus& outputs);

private:
    QString m_ExpectedString;
};

#endif	/* STRINGCONDITION_H */

