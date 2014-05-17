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
    void on_menuButton_toggled(bool);
    void on_buttonDebug_clicked();
    void on_buttonProfile_clicked();
    void on_buttonExport_clicked();
    void on_buttonSettings_clicked();
    void on_buttonSnapshot_clicked();
    
private:
    void updatePosition();
    
    Ui::CornerMenu* ui;
    FBPEditor* m_Editor;
};

#endif	/* _CORNERMENU_H */
