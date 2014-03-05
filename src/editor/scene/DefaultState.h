/* 
 * File:   DefaultState.h
 * Author: acailly
 *
 * Created on 5 mars 2014, 18:14
 */

#ifndef DEFAULTSTATE_H
#define	DEFAULTSTATE_H

#include <QtCore/QObject>
#include <QtGui/QGraphicsLineItem>

class DefaultState : public QObject {
    Q_OBJECT
    
public:
    DefaultState(QObject* parent = 0);
    virtual ~DefaultState();
    
protected:
    bool eventFilter(QObject *obj, QEvent *event);
    
private:
    QGraphicsLineItem* m_Arrow;
};

#endif	/* DEFAULTSTATE_H */

