/* 
 * File:   CircuitLoaderFromFBP.h
 * Author: acailly
 *
 * Created on 7 février 2014, 18:37
 */

#ifndef CIRCUITLOADERFROMFBP_H
#define	CIRCUITLOADERFROMFBP_H

#include <QtCore/QString>
#include <QtCore/QMap>
#include <QtCore/QMetaObject>

class QCircuit;

class CircuitLoaderFromFBP {
public:
    CircuitLoaderFromFBP();
    virtual ~CircuitLoaderFromFBP();
    
    QCircuit* loadFromFile(QString filePath) const;
    
    void addComponentClass(QString className, QMetaObject metaObject);
    
private:
    QMap<QString, QMetaObject> m_ComponentClasses;

};

#endif	/* CIRCUITLOADERFROMFBP_H */

