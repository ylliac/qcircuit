/* 
 * File:   ScriptAction.h
 * Author: acailly
 *
 * Created on 30 avril 2014, 16:51
 */

#ifndef SCRIPTCOMMAND_H
#define	SCRIPTCOMMAND_H

#include <QtCore/QRegExp>
#include <QtCore/QList>
#include <QtCore/QStringList>
#include <QtCore/QObject>

class ScriptCommand : public QObject{
    Q_OBJECT
    
public:
    ScriptCommand(QString command);
    virtual ~ScriptCommand();
    
    bool apply(QString input);
    
signals:
    void exec(QString arg1 = "", QString arg2 = "", QString arg3 = "", QString arg4 = "", QString arg5 = "");
    
private:
    QRegExp m_Regexp;
    QList<int> m_ParamOrder;

};

#endif	/* SCRIPTCOMMAND_H */

