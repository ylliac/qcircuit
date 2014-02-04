/* 
 * File:   AppendToTextEdit.h
 * Author: acailly
 *
 * Created on 29 janvier 2014, 18:14
 */

#ifndef APPENDTOTEXTEDIT_H
#define	APPENDTOTEXTEDIT_H

#include <dspatch/DspComponent.h>
#include <dspatch/DspSignalBus.h>

class QListWidget;

class AppendToTextEdit : public DspComponent{
public:
    AppendToTextEdit(QListWidget* textEdit);
    virtual ~AppendToTextEdit();
    
protected:
    virtual void Process_(DspSignalBus& inputs, DspSignalBus& outputs);
    
private:
    QListWidget* m_TextEdit;
};

#endif	/* APPENDTOTEXTEDIT_H */

