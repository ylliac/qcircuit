/* 
 * File:   BlockingQueue.cpp
 * Author: acailly
 * 
 * Created on 17 février 2014, 11:38
 */

#include "BlockingQueue.h"

template<typename Data>
BlockingQueue<Data>::BlockingQueue()
{
    closed = false;
}

template<typename Data>
BlockingQueue<Data>::~BlockingQueue()
{
    close();
}

template<typename Data>
void BlockingQueue<Data>::close()
{
    QMutexLocker locker(&mutex);
    if (!closed)
    {
        closed = true;
        queue.empty();
        monitor.wakeAll();
    }
}

template<typename Data>
int BlockingQueue<Data>::size() const
{
    // Make sure that the queue is not closed
    if (closed)
    {
        return 0;
    }

    return queue.size();
}

template<typename Data>
bool BlockingQueue<Data>::enqueue(Data data)
{
    QMutexLocker locker(&mutex);

    // Make sure that the queue is not closed
    if (closed)
    {
        return false;
    }

    queue.enqueue(data);

    // Signal all the waiting threads
    if (queue.size() == 1)
    {
        monitor.wakeAll();
    }

    return true;
}

template<typename Data>
bool BlockingQueue<Data>::dequeue(Data& value, unsigned long time)
{
    QMutexLocker locker(&mutex);

    // Block until something goes into the queue
    // or until the queue is closed
    while (queue.empty())
    {
        if (closed || !monitor.wait(&mutex, time))
        {
            return false;
        }
    }

    // Dequeue the next item from the queue
    value = queue.dequeue();
    
    return true;
}

template<typename Data>
bool BlockingQueue<Data>::empty() const
{
    return queue.empty();
}

template<typename Data>
void BlockingQueue<Data>::clear()
{
    QMutexLocker locker(&mutex);

    queue.clear();
}

