/* 
 * File:   Toast.h
 * Author: acailly
 *
 * Created on 4 juin 2014, 12:28
 */

#ifndef _TOAST_H
#define	_TOAST_H

#include <QtGui/QWidget>

class FBPEditor;

namespace Ui {
    class Toast;
}

class Toast : public QWidget {
    Q_OBJECT
    
public:
    static void make(FBPEditor* editor, QString text, int timeout = 2000);
    
protected:    
    Toast(QWidget* parent = 0, Qt::WindowFlags windowFlag = 0);
    virtual ~Toast();
    
    virtual bool eventFilter(QObject * watched, QEvent * event);
    
    QString text();
    void setText(QString text);
    
    void updatePosition();
        
private:
    Ui::Toast* ui;
};

#endif	/* _TOAST_H */
