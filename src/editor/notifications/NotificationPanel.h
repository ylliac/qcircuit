/* 
 * File:   NotificationPanel.h
 * Author: HOME
 *
 * Created on 21 avril 2014, 12:04
 */

#ifndef _NOTIFICATIONPANEL_H
#define	_NOTIFICATIONPANEL_H

#include "ui_NotificationPanel.h"

class NotificationPanel : public QMainWindow {
    Q_OBJECT
public:
    NotificationPanel(QWidget *parent = 0, Qt::WindowFlags flags = 0);
    virtual ~NotificationPanel();
private:
    Ui::NotificationPanel widget;
};

#endif	/* _NOTIFICATIONPANEL_H */
