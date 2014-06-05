/* 
 * File:   ArrowNotification.h
 * Author: acailly
 *
 * Created on 5 juin 2014, 17:30
 */

#ifndef _ARROWNOTIFICATION_H
#define	_ARROWNOTIFICATION_H

#include <QtGui/QWidget>

class FBPEditor;

namespace Ui {
    class ArrowNotification;
}

class ArrowNotification : public QWidget {
    Q_OBJECT
    
public:
    ArrowNotification(FBPEditor* editor);
    virtual ~ArrowNotification();
    
private slots:
    void on_buttonEdit_clicked();
    void on_buttonValidate_clicked();
    void on_buttonCancel_clicked();
    void on_buttonDelete_clicked();
    void on_editFrom_returnPressed();
    void onSelectionChanged();
    
private:
    void setReadOnly(bool readOnly);
    
    QString selectedFromPortName();
    void setSelectedFromPortName(QString name);
    
    void deleteSelectedBlock();
    
private:
    Ui::ArrowNotification* ui;   
    FBPEditor* m_Editor;
};

#endif	/* _ARROWNOTIFICATION_H */
