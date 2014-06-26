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
    void on_buttonEditFrom_clicked();
    void on_buttonValidateFrom_clicked();
    void on_buttonCancelFrom_clicked();
    void on_editFrom_returnPressed();
    
    void on_buttonEditTo_clicked();
    void on_buttonValidateTo_clicked();
    void on_buttonCancelTo_clicked();
    void on_editTo_returnPressed();

    void on_buttonDelete_clicked();    
    void onSelectionChanged();
    
private:
    void setReadOnlyFrom(bool readOnly);
    void setReadOnlyTo(bool readOnly);
    
    QString selectedFromPortName();
    void setSelectedFromPortName(QString name);
    
    QString selectedToPortName();
    void setSelectedToPortName(QString name);
    
    void deleteSelectedArrows();
    
private:
    Ui::ArrowNotification* ui;   
    FBPEditor* m_Editor;
};

#endif	/* _ARROWNOTIFICATION_H */
