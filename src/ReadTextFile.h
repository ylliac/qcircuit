/* 
 * File:   ReadTextFile.h
 * Author: acailly
 *
 * Created on 29 janvier 2014, 17:15
 */

#ifndef READTEXTFILE_H
#define	READTEXTFILE_H

#include <dspatch/DspComponent.h>
#include <dspatch/DspSignalBus.h>

#include <QtCore/QString>
#include <QtCore/QStringList>

class ReadTextFile : public DspComponent{
public:
    ReadTextFile(QString filePath);
    virtual ~ReadTextFile();
    
protected:
    virtual void Process_(DspSignalBus& inputs, DspSignalBus& outputs);
    
private:
    QString m_FilePath;
    QStringList m_FileContent;
    bool m_Trigger;

};

#endif	/* READTEXTFILE_H */

