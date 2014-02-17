/* 
 * File:   ReadTextFile.h
 * Author: acailly
 *
 * Created on 29 janvier 2014, 17:15
 */

#ifndef READTEXTFILE_H
#define	READTEXTFILE_H

#include <QtCore/QString>
#include <QtCore/QStringList>

#include "core/FBPComponent.h"

class ReadTextFile : public FBPComponent{
public:
    ReadTextFile(QString filePath);
    virtual ~ReadTextFile();
    
protected:
    virtual void execute();
    
private:
    QString m_FilePath;
    QStringList m_FileContent;
    bool m_Trigger;

};

#endif	/* READTEXTFILE_H */

