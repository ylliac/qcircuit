/* 
 * File:   Reader.h
 * Author: acailly
 *
 * Created on 3 février 2014, 12:17
 */

#ifndef READER_H
#define	READER_H

#include <dspatch/DspComponent.h>
#include <dspatch/DspSignalBus.h>

#include <QtCore/QTime>

class Reader : public DspComponent{
public:
    Reader();
    virtual ~Reader();
    
protected:
    virtual void Process_(DspSignalBus& inputs, DspSignalBus& outputs);
    
private:
    QTime m_Timer;

};

#endif	/* READER_H */

