/* 
 * File:   BlockNotification.h
 * Author: acailly
 *
 * Created on 29 avril 2014, 18:23
 */

#ifndef _BLOCKNOTIFICATION_H
#define	_BLOCKNOTIFICATION_H

#include <QtGui/QWidget>

class FBPEditor;

namespace Ui {
    class BlockNotification;
}

class BlockNotification : public QWidget {
    Q_OBJECT
    
public:
    BlockNotification(FBPEditor* editor);
    virtual ~BlockNotification();
    
private slots:
    void on_buttonEdit_clicked();
    void on_buttonValidate_clicked();
    void on_buttonCancel_clicked();
    void on_buttonDelete_clicked();
    void on_editName_returnPressed();
    void on_selection_changed();
    
private:
    void setReadOnly(bool readOnly);
    
    QString selectedBlockName();
    void setSelectedBlockName(QString name);
    
    void deleteSelectedBlock();
    
private:
    Ui::BlockNotification* ui;    
    FBPEditor* m_Editor;
};

#endif	/* _BLOCKNOTIFICATION_H */
