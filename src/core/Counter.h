/* 
 * File:   Counter.h
 * Author: acailly
 *
 * Created on 19 février 2014, 12:00
 */

#ifndef COUNTER_H
#define	COUNTER_H

#include <QtCore/QObject>
#include <QtCore/QAtomicInt>

class Counter : public QObject
{
    Q_OBJECT
    
public:
    Counter(QObject* parent = 0);
    virtual ~Counter();
    
    int count();

public slots:
    void increase();
    void decrease();
    
signals:
    void zero();

private:
    QAtomicInt counter;
};

#endif	/* COUNTER_H */

