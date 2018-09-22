#include "resizablestackedwidget.h"

ResizableStackedWidget::ResizableStackedWidget(QWidget *parent) : QStackedWidget (parent), m_iCurrentIdx(0)
{
    connect(this, SIGNAL(currentChanged(int)), SLOT(onCurrentChanged(int)));
}

int ResizableStackedWidget::addWidget(QWidget* pWidget)
{
   pWidget->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
   return QStackedWidget::addWidget(pWidget);
}

// FIXME: если изменится состав стека, метод будет работать не корректно
void ResizableStackedWidget::onCurrentChanged(int index)
{
   QWidget* pWidget = widget(m_iCurrentIdx);
   Q_ASSERT(pWidget);
   pWidget->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
   pWidget->adjustSize();

   pWidget = widget(index);
   Q_ASSERT(pWidget);
   pWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
   pWidget->adjustSize();
   adjustSize();

   m_iCurrentIdx = index;
}

