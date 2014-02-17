/* 
 * File:   NetworkLoaderFromFBP.h
 * Author: acailly
 *
 * Created on 17 février 2014, 14:50
 */

#ifndef NETWORKLOADERFROMFBP_H
#define	NETWORKLOADERFROMFBP_H

#include <QtCore/QString>
#include <QtCore/QMap>
#include <QtCore/QMetaObject>

class FBPNetwork;

class NetworkLoaderFromFBP {
public:
    NetworkLoaderFromFBP();
    virtual ~NetworkLoaderFromFBP();
    
    FBPNetwork* loadFromFile(QString filePath) const;
    
    void addComponentClass(QString className, QMetaObject metaObject);
    
private:
    QMap<QString, QMetaObject> m_ComponentClasses;
};

#endif	/* NETWORKLOADERFROMFBP_H */

