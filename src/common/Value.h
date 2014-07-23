/* 
 * File:   Value.h
 * Author: acailly
 *
 * Created on 23 juillet 2014, 18:27
 */

#ifndef VALUE_H
#define	VALUE_H

#include "../core/FBPComponent.h"

class Value : public FBPComponent {
    Q_OBJECT
    
public:
    Q_INVOKABLE Value();
    virtual ~Value();
        
    QVariant get();
    void set(QVariant value);
    
protected:
    virtual void execute();
    
private:
    QVariant value;
};

#endif	/* VALUE_H */

