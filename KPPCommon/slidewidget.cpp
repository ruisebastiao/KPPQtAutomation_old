#include "slidewidget.h"

SlideWidget::SlideWidget(QWidget *parent) :
    QWidget(parent),
    m_displayed(false)
{

}
bool SlideWidget::Displayed() const
{
    return m_displayed;
}

void SlideWidget::setDisplayed(bool displayed)
{
    m_displayed = displayed;
}

