/* 
 * File:   WindowButton.cpp
 * Author: HOME
 * 
 * Created on 30 avril 2014, 23:43
 */

#include "WindowButton.h"

#include <QtGui/QPainter>

WindowButton::WindowButton(ButtonType type, QWidget *parent) : QAbstractButton(parent),
m_Type(type),
m_State(STATE_NORMAL),
m_Normal(NULL),
m_Hovered(NULL),
m_Clicked(NULL) {
}

WindowButton::~WindowButton() {
    delete m_Normal;
    delete m_Hovered;
    delete m_Clicked;
}

void WindowButton::resizeEvent(QResizeEvent *event) {
    Q_UNUSED(event);

    initPixmaps();
}

void WindowButton::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);

    QPainter painter(this);

    if (isEnabled()) {
        switch (m_State) {
            case STATE_NORMAL:
                if (m_Normal != NULL) painter.drawPixmap(0, 0, *m_Normal);
                break;
            case STATE_HOVERED:
                if (m_Hovered != NULL) painter.drawPixmap(0, 0, *m_Hovered);
                break;
            case STATE_CLICKED:
                if (m_Clicked != NULL) painter.drawPixmap(0, 0, *m_Clicked);
                break;
        }
    } else {
        if (m_Normal != NULL) painter.drawPixmap(0, 0, *m_Normal);
    }
}

void WindowButton::initPixmaps() {
    // Delete previous button
    initPixmap(&m_Normal);
    initPixmap(&m_Hovered);
    initPixmap(&m_Clicked);

    switch (m_Type) {
        case BUTTON_MINIMIZE:
            initMinimize();
            break;
        case BUTTON_MAXIMIZE:
            initMaximize();
            break;
        case BUTTON_CLOSE:
            initClose();
            break;
    }
}

void WindowButton::initPixmap(QPixmap **pixmap) {
    delete *pixmap;

    *pixmap = new QPixmap(size());

    (*pixmap)->fill(Qt::transparent);
}

void WindowButton::initMinimize() {
    /********** Button's symbol **********/
    QPolygon symbol;

    symbol << QPoint(4, height() - 8)
            << QPoint(width() - 4, height() - 8)
            << QPoint(width() - 4, height() - 4)
            << QPoint(4, height() - 4);
    /*************************************/

    QPainter painter;

    /********** Normal **********/
    painter.begin(m_Normal);

    painter.setPen(Qt::NoPen);
    painter.setBrush(QBrush(Qt::black));

    painter.drawPolygon(symbol);

    painter.end();
    /****************************/

    /********** Hovered **********/
    painter.begin(m_Hovered);

    painter.setPen(Qt::NoPen);
    painter.setBrush(QBrush(Qt::white));

    painter.drawPolygon(symbol);

    painter.end();
    /*****************************/

    /********** Clicked **********/
    painter.begin(m_Clicked);

    painter.setPen(Qt::NoPen);
    painter.setBrush(QBrush(Qt::white));

    painter.drawPolygon(symbol);

    painter.end();
    /*****************************/
}

void WindowButton::initMaximize() {

    /********** Button's symbol **********/
    QPolygon symbol1, symbol2;

    symbol1 << QPoint(4, 4)
            << QPoint(width() - 4, 4)
            << QPoint(width() - 4, 8)
            << QPoint(4, 8);

    symbol2 << QPoint(4, 8)
            << QPoint(width() - 4, 8)
            << QPoint(width() - 4, height() - 4)
            << QPoint(4, height() - 4);
    /*************************************/

    QPainter painter;

    /********** Normal **********/
    painter.begin(m_Normal);

    painter.setPen(QPen(Qt::black));
    painter.setBrush(QBrush(Qt::black));

    painter.drawPolygon(symbol1);

    painter.setPen(QPen(Qt::black));
    painter.setBrush(Qt::NoBrush);

    painter.drawPolygon(symbol2);

    painter.end();
    /****************************/

    /********** Hovered **********/
    painter.begin(m_Hovered);

    painter.setPen(QPen(Qt::white));
    painter.setBrush(QBrush(Qt::white));

    painter.drawPolygon(symbol1);

    painter.setPen(QPen(Qt::white));
    painter.setBrush(Qt::NoBrush);

    painter.drawPolygon(symbol2);

    painter.end();
    /*****************************/

    /********** Clicked **********/
    painter.begin(m_Clicked);

    painter.setPen(QPen(Qt::white));
    painter.setBrush(QBrush(Qt::white));

    painter.drawPolygon(symbol1);

    painter.setPen(QPen(Qt::white));
    painter.setBrush(Qt::NoBrush);

    painter.drawPolygon(symbol2);

    painter.end();
    /*****************************/
}

void WindowButton::initClose() {

    /********** Button's symbol **********/
    QLine symbol1(QPoint(4, 4), QPoint(width() - 5, height() - 5));
    QLine symbol2(QPoint(width() - 5, 4), QPoint(4, height() - 5));
    /*************************************/

    QPainter painter;

    /********** Normal **********/
    painter.begin(m_Normal);

    painter.setPen(QPen(QBrush(Qt::black), 2.0));

    painter.drawLine(symbol1);
    painter.drawLine(symbol2);

    painter.end();
    /****************************/

    /********** Hovered **********/
    painter.begin(m_Hovered);

    painter.setPen(QPen(QBrush(Qt::white), 2.0));

    painter.drawLine(symbol1);
    painter.drawLine(symbol2);

    painter.end();
    /*****************************/

    /********** Clicked **********/
    painter.begin(m_Clicked);

    painter.setPen(QPen(QBrush(Qt::white), 2.0));

    painter.drawLine(symbol1);
    painter.drawLine(symbol2);

    painter.end();
    /*****************************/
}

void WindowButton::enterEvent(QEvent *event) {
    Q_UNUSED(event);

    m_State = STATE_HOVERED;

    update();
}

void WindowButton::leaveEvent(QEvent *event) {
    Q_UNUSED(event);

    m_State = STATE_NORMAL;

    update();
}

void WindowButton::mousePressEvent(QMouseEvent *event) {
    QAbstractButton::mousePressEvent(event);

    m_State = STATE_CLICKED;

    update();
}

void WindowButton::mouseReleaseEvent(QMouseEvent *event) {
    QAbstractButton::mouseReleaseEvent(event);

    if (underMouse()) m_State = STATE_HOVERED;
    else m_State = STATE_NORMAL;

    update();
}

