/* 
 * File:   FBPPort.h
 * Author: acailly
 *
 * Created on 17 février 2014, 09:55
 */

#ifndef FBPPORT_H
#define	FBPPORT_H

#include <QtCore/QObject>
#include <QtCore/QString>

class FBPPort : public QObject {
    Q_OBJECT
    
public:
    FBPPort(QString name);
    virtual ~FBPPort();

    QString getName();
    
private:
    QString name;
};

#endif	/* FBPPORT_H */

