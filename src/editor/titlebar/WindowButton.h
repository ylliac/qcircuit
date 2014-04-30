/* 
 * File:   WindowButton.h
 * Author: HOME
 *
 * Created on 30 avril 2014, 23:43
 */

#ifndef WINDOWBUTTON_H
#define	WINDOWBUTTON_H

#include <QtGui/QAbstractButton>
#include <QtGui/QPixmap>

class WindowButton : public QAbstractButton {

    Q_OBJECT

public:
    enum ButtonType {
        BUTTON_MINIMIZE, BUTTON_MAXIMIZE, BUTTON_CLOSE
    };

    WindowButton(ButtonType type, QWidget *parent = 0);
    ~WindowButton();

protected:
    void resizeEvent(QResizeEvent *event);
    void paintEvent(QPaintEvent *event);
    void enterEvent(QEvent *event);
    void leaveEvent(QEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

private:

    enum ButtonState {
        STATE_NORMAL, STATE_HOVERED, STATE_CLICKED
    };

    ButtonType m_Type;
    ButtonState m_State;
    QPixmap *m_Normal;
    QPixmap *m_Hovered;
    QPixmap *m_Clicked;

    void initPixmaps();
    void initPixmap(QPixmap **pixmap);
    void initMinimize();
    void initMaximize();
    void initClose();
};

#endif	/* WINDOWBUTTON_H */

