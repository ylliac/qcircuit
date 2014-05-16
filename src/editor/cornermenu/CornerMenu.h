/* 
 * File:   CornerMenu.h
 * Author: acailly
 *
 * Created on 16 mai 2014, 09:37
 */

#ifndef _CORNERMENU_H
#define	_CORNERMENU_H

#include <QtGui/QWidget>

class FBPEditor;
class QEvent;

namespace Ui {
    class CornerMenu;
}

class CornerMenu : public QWidget {
    Q_OBJECT

public:
    CornerMenu(FBPEditor* editor);
    virtual ~CornerMenu();

    virtual bool eventFilter(QObject * watched, QEvent * event);

private slots:
    void showMenu(bool);
    
private:
    void updatePosition();
    
    Ui::CornerMenu* ui;
};

#endif	/* _CORNERMENU_H */
