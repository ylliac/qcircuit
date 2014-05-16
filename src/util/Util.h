/* 
 * File:   Util.h
 * Author: acailly
 *
 * Created on 25 février 2014, 11:24
 */

#ifndef UTIL_H
#define	UTIL_H

#include <QtCore/QVariant>

#define CONNECT(sender, signal, receiver, slot) \
if(!QObject::connect(sender, signal, receiver, slot)){\
    QString msg = QString("Error while connecting signal '%1' from '%2' to slot '%3' from '%4'").arg(#signal).arg(#sender).arg(#slot).arg(#receiver);\
    Q_ASSERT(false);\
}

class QWidget;

class Util {
public:
    virtual ~Util(){};
    
    template <class T> 
    static T* toPointer(QVariant v)
    {
        return (T *) v.value<void *>();
    }

    template <class T> 
    static QVariant toQVariant(T* ptr)
    {
        return qVariantFromValue((void *) ptr);
    }
    
    static void fadeIn(QWidget* widget);
    static void fadeOut(QWidget* widget);

};

#endif	/* UTIL_H */

