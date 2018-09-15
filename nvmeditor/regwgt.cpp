#include "regwgt.h"


regWidget_c::regWidget_c(QWidget *pwgt) : m_layout(new QVBoxLayout)
{

}

regWidget_c::~regWidget_c(){}

void regWidget_c::Build() noexcept
{
    reg_c &reg = *m_reg;    // только удобства ради, простите.
    QLabel *pLbl;
    QLineEdit *pLe;

    // TODO: удалить ранее созданные компоненты!
    // removeChild() или что-то вроде того
    // и не забыть очистить контейнер

    for (int i = 0; i < static_cast<int>(reg.GetFieldsCount()); i++)
    {
        try
        {
            pLbl = new QLabel(QString::fromStdString(reg[i].first), this);
            pLe = new QLineEdit(QString::number(reg[i].second, 16), this);
        } catch (regExc_c &exc) {
            exc.ToStderr();
            return;
        }
        QHBoxLayout *playout = new QHBoxLayout;
        playout->addWidget(pLbl);
        playout->addStretch(1);
        playout->addWidget(pLe);
        m_layout->addLayout(playout);
    }

    setLayout(m_layout);

    resize(400, 300);
}

dummyReg_c::dummyReg_c()
{
    createReg();
    Build();
}
dummyReg_c::~dummyReg_c(){}
