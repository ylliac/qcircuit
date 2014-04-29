/* 
 * File:   BlockNotification.h
 * Author: acailly
 *
 * Created on 29 avril 2014, 18:23
 */

#ifndef _BLOCKNOTIFICATION_H
#define	_BLOCKNOTIFICATION_H

#include <QtGui/QWidget>

namespace Ui {
    class BlockNotification;
}

class BlockNotification : public QWidget {
    Q_OBJECT
public:
    BlockNotification(QWidget* parent = 0, Qt::WindowFlags windowFlag = 0);
    virtual ~BlockNotification();
    
private slots:
    void on_buttonEdit_clicked();
    void on_buttonValidate_clicked();
    
private:
    void setReadOnly(bool readOnly);
    
private:
    Ui::BlockNotification* ui;
};

#endif	/* _BLOCKNOTIFICATION_H */
