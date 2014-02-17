/* 
 * File:   BlockingQueue.h
 * Author: acailly
 *
 * Created on 17 février 2014, 11:38
 */

#ifndef BLOCKINGQUEUE_H
#define	BLOCKINGQUEUE_H

#include <limits.h>
#include <QtCore/QMutex>
#include <QtCore/QQueue>
#include <QtCore/QWaitCondition>

template<typename Data>
class BlockingQueue {
public:
    BlockingQueue();
    virtual ~BlockingQueue();
    
    void close();
    bool enqueue(Data data);
    bool dequeue(Data& value, unsigned long time = ULONG_MAX);
    int size() const;

private:
    QMutex mutex;
    QWaitCondition monitor;
    volatile bool closed;
    QQueue<Data> queue;
};

#endif	/* BLOCKINGQUEUE_H */

