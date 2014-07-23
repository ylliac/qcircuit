/* 
 * File:   IIP.h
 * Author: HOME
 *
 * Created on 23 juillet 2014, 20:44
 */

#ifndef IIP_H
#define	IIP_H

#include "../core/FBPComponent.h"

#include <QtCore/QList>
#include <QtCore/QQueue>

class IIP : public FBPComponent {
    Q_OBJECT
    
public:
    Q_INVOKABLE IIP(QList<QVariant> packets);
    virtual ~IIP();
    
protected:
    virtual void execute();
    
private:
    QQueue<QVariant> packets;
};

#endif	/* IIP_H */

