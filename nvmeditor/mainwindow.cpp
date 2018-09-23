#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDir>
#include <iostream>
#include <QFileDialog>
#include <QMessageBox>
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
    connect(ui->cbName, SIGNAL(currentIndexChanged(int)), SLOT(slotRegIndexChanged(int)));
    connect(ui->maOpen, SIGNAL(triggered(bool)), SLOT(slotOpenFile()));
    connect(ui->maSave, SIGNAL(triggered(bool)), SLOT(slotSaveFile()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::slotOpenFile() noexcept
{
    QString qstr = QFileDialog::getOpenFileName(this, "Загрузить NVM-образ", m_qstrCurrentPath, "*.eep");
    if (!qstr.isEmpty())
    {
        // удаляем все
        ui->cbName->clear();
        destroyStackedWidget();

        // загружаем новый образ
        try {
            reg_c::LoadNVMImage(qstr.toStdString());
        } catch (regExc_c &exc) {
            exc.ToStderr();
            return;
        }

        // создаем виджеты с регистрами
        buildStackedWidget();
        if (m_pstk != nullptr)
        {
            ui->saRegView->setWidget(m_pstk);
            for (int i = 0; i < m_pstk->count(); i++)
                ui->cbName->addItem(QString::fromStdString(qobject_cast<regWidget_c*>(m_pstk->widget(i))->RegName()));
        }
    }
}

void MainWindow::slotSaveFile() noexcept
{
    QString qstr = QFileDialog::getSaveFileName(this, "Сохранить NVM-образ", m_qstrCurrentPath, "*.eep");
    if (!qstr.isEmpty())
    {
        try {
            reg_c::SaveNVMImage(qstr.toStdString());
        } catch (regExc_c &exc) {
            exc.ToStderr();
        }
        QString msg{"Образ успешно сохранен в файл:\r\n"};
        msg.append(qstr);
        QMessageBox::information(this, "Сохранено ок", msg);
    }
}

void MainWindow::connectCurrentReg() noexcept
{
    connect(ui->pbDefault, SIGNAL(clicked()), m_pstk->currentWidget(), SLOT(slotRestoreReg()));
    connect(ui->pbOk, SIGNAL(clicked()), m_pstk->currentWidget(), SLOT(slotSaveReg()));
}

void MainWindow::disconnectCurrentReg() noexcept
{
    disconnect(ui->pbDefault, SIGNAL(clicked()), m_pstk->currentWidget(), SLOT(slotRestoreReg()));
    disconnect(ui->pbOk, SIGNAL(clicked()), m_pstk->currentWidget(), SLOT(slotSaveReg()));
}

void MainWindow::buildStackedWidget() noexcept
{
    std::unique_ptr<ResizableStackedWidget> pstk = std::make_unique<ResizableStackedWidget>();
    try {
        pstk->addWidget(new regWgtViewer_c<regInitControl1_c>());
        pstk->addWidget(new regWgtViewer_c<regPCIeInitConfiguration3_c>());
    } catch (regExc_c &exc) {
        exc.ToStderr();
        std::ostringstream oss;
        oss << "created successfully: " << pstk->count() << " widgets";
        TRACE_BY_STREAM(oss);
        return;
    }
    pstk->setCurrentIndex(0);
    m_pstk = pstk.release();
    connectCurrentReg();
}

void MainWindow::destroyStackedWidget() noexcept
{
    // NB: все сигнально-слотовые связи разорвутся автоматически
    if (m_pstk != nullptr)
    {
        for (int i = 0; i < m_pstk->count(); i++)
        {
            QWidget *pwgt = m_pstk->widget(i);
            m_pstk->removeWidget(pwgt);
        }
        delete  m_pstk;
        m_pstk = nullptr;
    }
}

void MainWindow::slotRegIndexChanged(int index) noexcept
{
    if (m_pstk != nullptr)
    {
        disconnectCurrentReg();
        m_pstk->setCurrentIndex(index);
        connectCurrentReg();
    }
}

