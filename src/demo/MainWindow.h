/* 
 * File:   MainWindow.h
 * Author: acailly
 *
 * Created on 29 janvier 2014, 18:21
 */

#ifndef _MAINWINDOW_H
#define	_MAINWINDOW_H

#include <QtGui/QMainWindow>

class FBPNetwork;

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT
    
public:
    MainWindow(QWidget* parent = 0, Qt::WindowFlags windowFlag = 0);
    virtual ~MainWindow();
    
private slots:
    void launchNetwork();
    
private:
    Ui::MainWindow* ui;
    FBPNetwork* m_Network;
};

#endif	/* _MAINWINDOW_H */
