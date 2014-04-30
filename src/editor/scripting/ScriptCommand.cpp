/* 
 * File:   ScriptAction.cpp
 * Author: acailly
 * 
 * Created on 30 avril 2014, 16:51
 */

#include "ScriptCommand.h"

ScriptCommand::ScriptCommand(QString step)
{
    QRegExp paramRegexp("\\$(\\d+)");
    int pos = 0;
    while ((pos = paramRegexp.indexIn(step, pos)) != -1) {
        m_ParamOrder.append(paramRegexp.cap(1).toInt());
        pos += paramRegexp.matchedLength();
    }

    QString regexpPattern = step;
    regexpPattern = regexpPattern.replace(paramRegexp, "(.+)");    

    m_Regexp = QRegExp(regexpPattern);
}

ScriptCommand::~ScriptCommand()
{
}

bool ScriptCommand::apply(QString input)
{
    bool result = false;

    if(m_Regexp.exactMatch(input)){
        QStringList args;
        for (int i = 0; i < 5; i++)
        {
            args.append("");
        }

        int captureCount = m_Regexp.captureCount();
        for (int i = 1; i <= captureCount; i++)
        {
            QString arg = m_Regexp.cap(i);
            int argIndex = m_ParamOrder.at(i-1);
            args[argIndex-1] = arg;
        }

        emit exec(args.at(0), args.at(1), args.at(2), args.at(3), args.at(4));

        result = true;
    }

    return result;
}

