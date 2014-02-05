/* 
 * File:   QCircuit.h
 * Author: acailly
 *
 * Created on 4 février 2014, 11:30
 */

#ifndef QCIRCUIT_H
#define	QCIRCUIT_H

#include <dspatch/DspCircuit.h>

#include <QtCore/QObject>

class QCircuit : public QObject, public DspCircuit {
    Q_OBJECT

public:
    QCircuit();
    virtual ~QCircuit();

    bool ConnectOutToIn(const QString& fromComponentAndPort, const QString& toComponentAndPort);
};

#endif	/* QCIRCUIT_H */

