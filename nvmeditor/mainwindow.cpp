#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDir>
#include <iostream>
#include <QFileDialog>
#include "resizablestackedwidget.h"

#include "reg.h"
#include "regwgt.h"
#include "regmap.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_qstrCurrentPath(QDir::currentPath())
{
    ui->setupUi(this);
    connect(ui->maOpen, SIGNAL(triggered(bool)), SLOT(slotOpenFile()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::slotOpenFile() noexcept
{
    // TODO: требуется перезагрузка всех регистров!
    QString qstr = QFileDialog::getOpenFileName(this, "Загрузить NVM-образ", m_qstrCurrentPath, "*.eep");
    if (qstr != "")
    {
        try {
            reg_c::LoadNVMImage(qstr.toStdString());
        } catch (regExc_c &exc) {
            exc.ToStderr();
        }
        buildStackedWidget();
        ui->saRegView->setWidget(m_pstk);
    }
}

void MainWindow::buildStackedWidget() noexcept
{
    std::unique_ptr<ResizableStackedWidget> pstk = std::make_unique<ResizableStackedWidget>();
    try {
        pstk->addWidget(new regWgtViewer_c<regInitControl1_c>());
        pstk->addWidget(new regWgtViewer_c<regPCIeInitConfiguration3_c>());
    } catch (regExc_c &exc) {
        exc.ToStderr();
    }
    pstk->setCurrentIndex(0);
    m_pstk = pstk.release();
}
