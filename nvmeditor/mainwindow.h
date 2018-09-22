#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class ResizableStackedWidget;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QString m_qstrCurrentPath;
    ResizableStackedWidget *m_pstk = nullptr;

    void buildStackedWidget() noexcept;

private slots:
    void slotOpenFile() noexcept;
};

#endif // MAINWINDOW_H
