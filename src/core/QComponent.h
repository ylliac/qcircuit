/* 
 * File:   QComponent.h
 * Author: acailly
 *
 * Created on 4 février 2014, 11:25
 */

#ifndef QCOMPONENT_H
#define	QCOMPONENT_H

#include <dspatch/DspComponent.h>
#include <dspatch/DspSignalBus.h>

#include <QtCore/QObject>

class QComponent : public QObject, public DspComponent{
    Q_OBJECT
    
public:
    static const QString METADATA_IN;
    static const QString METADATA_OUT;
    
    QComponent();
    virtual ~QComponent();

protected:
    virtual void Process_(DspSignalBus& inputs, DspSignalBus& outputs)=0;
    
protected:
    void createInOutFromMetadata();
    
};

#endif	/* QCOMPONENT_H */

