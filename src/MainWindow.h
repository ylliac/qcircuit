/* 
 * File:   MainWindow.h
 * Author: acailly
 *
 * Created on 29 janvier 2014, 18:21
 */

#ifndef _MAINWINDOW_H
#define	_MAINWINDOW_H

#include <QtGui/QMainWindow>

class QCircuit;

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT
    
public:
    MainWindow(QWidget* parent = 0, Qt::WindowFlags windowFlag = 0);
    virtual ~MainWindow();
    
private slots:
    void launchCircuit();
    
private:
    Ui::MainWindow* ui;
    QCircuit* m_Circuit;
};

#endif	/* _MAINWINDOW_H */
