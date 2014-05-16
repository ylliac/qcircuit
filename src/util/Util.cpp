/* 
 * File:   Util.cpp
 * Author: acailly
 * 
 * Created on 25 février 2014, 11:24
 */

#include "Util.h"

#include <QtGui/QWidget>
#include <QtGui/QGraphicsOpacityEffect>
#include <QtCore/QPropertyAnimation>
#include <QtCore/QEasingCurve>
#include <QtCore/QAbstractAnimation>

void Util::fadeIn(QWidget* widget)
{    
    double startOpacity;
    double endOpacity = 1.0;
    if(widget->isVisible())
    {
        startOpacity = 1.0;
    }
    else
    {
        startOpacity = 0.0;
    }
    
    if(startOpacity != endOpacity)
    {    
        widget->setVisible(true);
        
        QGraphicsOpacityEffect* opacityEffect = new QGraphicsOpacityEffect(widget);
        opacityEffect->setOpacity(startOpacity);
        widget->setGraphicsEffect(opacityEffect);

        QPropertyAnimation* animation = new QPropertyAnimation(widget);
        animation->setTargetObject(opacityEffect);
        animation->setPropertyName("opacity");
        animation->setDuration(500);
        animation->setStartValue(opacityEffect->opacity());
        animation->setEndValue(endOpacity);
        animation->setEasingCurve(QEasingCurve::OutQuad);
        animation->start(QAbstractAnimation::DeleteWhenStopped);
        
        CONNECT(animation, SIGNAL(finished()), widget, SLOT(update()));  
    }
}
    
void Util::fadeOut(QWidget* widget)
{
    double startOpacity;
    double endOpacity = 0.0;
    if(widget->isVisible())
    {
        startOpacity = 1.0;
    }
    else
    {
        startOpacity = 0.0;
    }
    
    if(startOpacity != endOpacity)
    {
        QGraphicsOpacityEffect* opacityEffect = new QGraphicsOpacityEffect(widget);
        opacityEffect->setOpacity(startOpacity);
        widget->setGraphicsEffect(opacityEffect);

        QPropertyAnimation* animation = new QPropertyAnimation(widget);
        animation->setTargetObject(opacityEffect);
        animation->setPropertyName("opacity");
        animation->setDuration(200);
        animation->setStartValue(opacityEffect->opacity());
        animation->setEndValue(endOpacity);
        animation->setEasingCurve(QEasingCurve::OutQuad);
        animation->start(QAbstractAnimation::DeleteWhenStopped);

        CONNECT(animation, SIGNAL(finished()), widget, SLOT(hide()));  
    }
}
