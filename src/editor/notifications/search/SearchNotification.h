/* 
 * File:   SearchNotification.h
 * Author: HOME
 *
 * Created on 30 avril 2014, 21:50
 */

#ifndef _SEARCHNOTIFICATION_H
#define	_SEARCHNOTIFICATION_H

#include <QtGui/QWidget>

class FBPEditor;

namespace Ui {
    class SearchNotification;
}

class SearchNotification : public QWidget {
    Q_OBJECT
public:
    SearchNotification(FBPEditor* editor);
    virtual ~SearchNotification();
    
private slots:
    void on_buttonAdd_clicked();    
    
private:
    Ui::SearchNotification* ui;    
    FBPEditor* m_Editor;
};

#endif	/* _SEARCHNOTIFICATION_H */
