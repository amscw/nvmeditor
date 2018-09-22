#include "regwgt.h"

std::string regWidgetExc_c::strErrorMessages[] = {
    "cannot save fields to register",
};


regWidgetExc_c::regWidgetExc_c(enum errCode_t code, const std::string &strFile, const std::string &strFunction, const std::string &strWhat) noexcept :
    exc_c(strFile, strFunction, strWhat), m_errCode(code)
{}

regWidget_c::regWidget_c(QWidget *pwgt) : QWidget(pwgt), m_playout(new QVBoxLayout)
{
    setLayout(m_playout);
}

regWidget_c::~regWidget_c(){}

void regWidget_c::destroy() noexcept
{
    QObjectList list = children();
    for (auto it : list)
    {
        QWidget *pwgt = qobject_cast<QWidget*>(&(*it));
        // варварство...
        if (pwgt != qobject_cast<QWidget*>(m_playout))
            delete pwgt;
    }
    m_qFields.clear();
}

void regWidget_c::build() noexcept
{
    reg_c &reg = *m_reg;    // только удобства ради, простите
    QLabel *pLbl;
    QLineEdit *pLe;
    QHBoxLayout *playout;

    for (int i = 0; i < static_cast<int>(reg.GetFieldsCount()); i++)
    {
        // создаем на каждой итерации пару виджетов
        try
        {
            pLbl = new QLabel(QString::fromStdString(reg[i].first), this);
            pLe = new QLineEdit(QString::number(reg[i].second, 16), this);
        } catch (regExc_c &exc) {
            exc.ToStderr();
            destroy();
            return;
        }
        pLe->setMaximumWidth(60);   // TODO: вычислить по шрифту так, чтобы влезло "FFFF"
        pLe->setAlignment(Qt::AlignmentFlag::AlignRight);

        // и пихаем ее в компоновку
        playout = new QHBoxLayout;
        playout->addWidget(pLbl);
        playout->addStretch(1);
        playout->addWidget(pLe);
        m_playout->addLayout(playout);

        // сохраняем указатели на них, чтобы иметь возможность обращаться к ним в дальнейшем
        m_qFields.push_back(QPair<QLabel*, QLineEdit*>(pLbl, pLe));
    }
}

void regWidget_c::slotSaveReg() noexcept
{
    reg_c &reg = *m_reg;    // только удобства ради, простите
    bool bOk;

    if (m_qFields.size() != static_cast<int>(reg.GetFieldsCount()))
    {
        // виджеты регистра не были созданы по каким-то причинам
        std::ostringstream oss;
        oss << "regwidget has only " << m_qFields.size() << "/" << reg.GetFieldsCount() << " fields";
        TRACE_BY_STREAM(oss);
        return;
    }

    for (int i = 0; i < static_cast<int>(reg.GetFieldsCount()); i++)
    {
        QString str = m_qFields[i].second->text();
        int tmp = str.toInt(&bOk, 16);
        if (!bOk)
        {
            // пользователь ввёл какую-то дичь. Сбрасываем это поле в дефолт
            std::ostringstream oss;
            oss << "cannot convert \"" << str.toStdString() << "\" to integer value. Restore to default";
            TRACE_BY_STREAM(oss);
            m_qFields[i].second->setText(QString::number(reg[i].second, 16));
            continue; // или return ? хз... По идее остальные поля можем попробовать сохранить
        }
        reg[i].second = static_cast<std::uint16_t>(tmp);
    }

    // грузим поля в бинарь
    reg.Save();
}

void regWidget_c::slotRestoreReg() noexcept
{
    reg_c &reg = *m_reg;    // только удобства ради, простите

    if (m_qFields.size() != static_cast<int>(reg.GetFieldsCount()))
    {
        // виджеты регистра не были созданы по каким-то причинам
        std::ostringstream oss;
        oss << "regwidget has only " << m_qFields.size() << "/" << reg.GetFieldsCount() << " fields";
        TRACE_BY_STREAM(oss);
        return;
    }

    // перезагружаем регистр
    reg.ToDefault();

    // устанавливаем текстовые поля виджета
    for (int i = 0; i < static_cast<int>(reg.GetFieldsCount()); i++)
        m_qFields[i].second->setText(QString::number(reg[i].second, 16));
}
