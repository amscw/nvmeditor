#ifndef REGWGT_H
#define REGWGT_H

#include <QWidget>
// TODO: убрать отсюда, заменив на incompelte types
#include <QVector>
#include <QLabel>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QVBoxLayout>

#include "reg.h"

struct regWidgetExc_c : public exc_c
{
    enum class errCode_t : std::uint32_t {
        ERR_SAVE,
    } m_errCode;

    regWidgetExc_c(enum errCode_t code, const std::string &strFile, const std::string &strFunction, const std::string &strWhat = "") noexcept;

    const std::string &Msg() const noexcept override { return strErrorMessages[static_cast<int>(m_errCode)]; }
    void ToStderr() const noexcept override
    {
        std::cerr << "WTF:" << m_strFile << "(" << m_strFunction << "):" << strErrorMessages[static_cast<int>(m_errCode)] << "-" << m_strWhat<< std::endl;
    }

private:
    static std::string strErrorMessages[];
};



/**
 * @brief The regView_c class
 * Увы, Qt-шные классы не могут быть template'ами.
 */

class regWidget_c : public QWidget
{
    Q_OBJECT

private:
    QVector<QPair<QLabel*, QLineEdit*>> m_qFields;
    QVBoxLayout *m_playout = nullptr;
    const std::string fakeName = "not created";

protected:
    std::unique_ptr<reg_c> m_reg = nullptr;
    virtual void createReg() = 0;
    /**
     * @brief Build
     * Логика построения виджета остается неизменной для любого регистра,
     * т.к. зависит только от абстракции регистра!
     * (в терминах паттерна "фабричный метод" - это Creator)
     */
    void build() noexcept;
    void destroy() noexcept;

public:
    regWidget_c(QWidget *pwgt = nullptr);
    virtual ~regWidget_c();

    const std::string &RegName() const noexcept {
        if (m_reg != nullptr)
            return m_reg->Name();
        else return fakeName;
    }

public slots:
    void slotSaveReg() noexcept;
    void slotRestoreReg() noexcept;
};

template<typename regType>
class regWgtViewer_c : public regWidget_c
{
    void createReg()
    {
        std::unique_ptr<reg_c> p;
        try {
            p = std::make_unique<regType>();
        } catch (regExc_c &) {
            throw ;
        }
        m_reg.swap(p);
    }

public:
    regWgtViewer_c(QWidget *pwgt = nullptr) : regWidget_c(pwgt)
    {
        try {
            createReg();
        } catch (regExc_c &) {
            throw;
        }
        build();
    }
};

#endif // REGWGT_H
