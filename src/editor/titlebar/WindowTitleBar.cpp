/*
 * File:   WindowTitleBar.cpp
 * Author: HOME
 *
 * Created on 30 avril 2014, 22:41
 */

#include "WindowTitleBar.h"

#include <QtGui/QPainter>
#include <QtGui/QPen>
#include <QtCore/QDebug>
#include <QtCore/QCoreApplication>

#include "util/Util.h"

WindowTitleBar::WindowTitleBar(QWidget *parent) :
QWidget(parent),
m_Cache(NULL),
m_Title(this),
m_Minimize(WindowButton::BUTTON_MINIMIZE, this),
m_Maximize(WindowButton::BUTTON_MAXIMIZE, this),
m_Close(WindowButton::BUTTON_CLOSE, this) {
    setFixedHeight(24);
    m_Title.setStyleSheet("color: white; font-family: Sans; font-weight: bold; font-size: 14px");
    updateWindowTitle();
    CONNECT(&m_Minimize, SIGNAL(clicked()),
            this, SLOT(minimized()));

    CONNECT(&m_Maximize, SIGNAL(clicked()),
            this, SLOT(maximized()));

    CONNECT(&m_Close, SIGNAL(clicked()),
            this, SLOT(quit()));
}

WindowTitleBar::~WindowTitleBar() {
}

void WindowTitleBar::resizeEvent(QResizeEvent *event) {
    Q_UNUSED(event);

    delete m_Cache; // Remove old cache
    
    m_Cache = new QPixmap(size()); // Create a cache with same size as the widget
    m_Cache->fill(Qt::black); 

    QPainter painter(m_Cache); // Start painting the cache
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setRenderHint(QPainter::HighQualityAntialiasing, true);

    m_Title.move(28, 2);
    m_Title.resize(width() - 116, 20);

    m_Minimize.move(width() - 90, 2);
    m_Minimize.resize(20, 20);

    m_Maximize.move(width() - 60, 2);
    m_Maximize.resize(20, 20);

    m_Close.move(width() - 30, 2);
    m_Close.resize(20, 20);
}

void WindowTitleBar::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);

    if (m_Cache != NULL) {
        QPainter painter(this);

        painter.drawPixmap(0, 0, *m_Cache);
    }
}

void WindowTitleBar::updateWindowTitle() {
    m_Title.setText(window()->windowTitle());
}

void WindowTitleBar::minimized() {
    window()->showMinimized();
}

void WindowTitleBar::maximized() {
    if (window()->windowState() == Qt::WindowMaximized) {
        window()->showNormal();
    } else {
        window()->showMaximized();
    }
}

void WindowTitleBar::quit() {
    qApp->quit();
}

void WindowTitleBar::mousePressEvent(QMouseEvent *event) {
    m_Diff = event->pos();

    setCursor(QCursor(Qt::SizeAllCursor));
}

void WindowTitleBar::mouseReleaseEvent(QMouseEvent *event) {
    Q_UNUSED(event);

    setCursor(QCursor(Qt::ArrowCursor));
}

void WindowTitleBar::mouseMoveEvent(QMouseEvent *event) {
    QPoint p = event->globalPos();

    window()->move(p - m_Diff);
}
