#include "resizablestackedwidget.h"

ResizableStackedWidget::ResizableStackedWidget(QWidget *parent) : QStackedWidget (parent)
{
    connect(this, SIGNAL(currentChanged(int)), SLOT(onCurrentChanged(int)));
}

int ResizableStackedWidget::addWidget(QWidget* pWidget)
{
   pWidget->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
   return QStackedWidget::addWidget(pWidget);
}

void ResizableStackedWidget::onCurrentChanged(int index)
{
   QWidget* pWidget = widget(index);
   Q_ASSERT(pWidget);
   pWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
   pWidget->adjustSize();
   adjustSize();
}
