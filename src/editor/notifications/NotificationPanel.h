/* 
 * File:   NotificationPanel.h
 * Author: HOME
 *
 * Created on 21 avril 2014, 17:30
 */

#ifndef _NOTIFICATIONPANEL_H
#define	_NOTIFICATIONPANEL_H

#include <QtGui/QWidget>
#include <QtGui/QVBoxLayout>

class FBPEditor;

namespace Ui {
    class NotificationPanel;
}

class NotificationPanel : public QWidget {
    Q_OBJECT
    
public:
    NotificationPanel(FBPEditor* editor);
    virtual ~NotificationPanel();
    
    void addNotification(QWidget* notification);
    
private:
    Ui::NotificationPanel* ui;    
    FBPEditor* m_Editor; 
    QVBoxLayout* m_Layout;
};

#endif	/* _NOTIFICATIONPANEL_H */
