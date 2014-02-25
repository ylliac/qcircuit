/* 
 * File:   GUIThreadExecutor.h
 * Author: acailly
 *
 * Created on 25 février 2014, 17:29
 */

#ifndef GUITHREADEXECUTOR_H
#define	GUITHREADEXECUTOR_H

#include <QtCore/QObject>

class GUIThreadExecutor : public QObject{
    Q_OBJECT
    
public:
    GUIThreadExecutor();
    virtual ~GUIThreadExecutor();
    
    void execute(QObject* obj, const char* member, bool blocking);
    
private slots:
    void executionRequested(QObject* obj, const char* member);    
};

#endif	/* GUITHREADEXECUTOR_H */

