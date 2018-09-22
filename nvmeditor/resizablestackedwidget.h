#ifndef RESIZABLESTACKEDWIDGET_H
#define RESIZABLESTACKEDWIDGET_H

#include <QStackedWidget>

class ResizableStackedWidget : public QStackedWidget
{
    Q_OBJECT

private:
    int m_iCurrentIdx;

public:
    ResizableStackedWidget(QWidget *parent = nullptr);
    int addWidget(QWidget *widget);

public slots:
    void onCurrentChanged(int index);
};

#endif // RESIZABLESTACKEDWIDGET_H
