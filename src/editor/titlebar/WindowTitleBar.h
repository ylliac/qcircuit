/* 
 * File:   WindowTitleBar.h
 * Author: HOME
 *
 * Created on 30 avril 2014, 22:41
 */

#ifndef _WINDOWTITLEBAR_H
#define	_WINDOWTITLEBAR_H

#include <QtGui/QWidget>
#include <QtGui/QPixmap>
#include <QtGui/QLabel>
#include <QtGui/QMouseEvent>

#include "WindowButton.h"

class WindowTitleBar : public QWidget {
    Q_OBJECT

public:
    WindowTitleBar(QWidget *parent = 0);
    ~WindowTitleBar();

public slots:
    void updateWindowTitle();
    void minimized();
    void maximized();
    void quit();

protected:
    void resizeEvent(QResizeEvent *event);
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

private:
    QPixmap* m_Cache;
    QLabel m_Title;
    WindowButton m_Minimize;
    WindowButton m_Maximize;
    WindowButton m_Close;
    QPoint m_Diff;
};

#endif	/* _WINDOWTITLEBAR_H */
