#ifndef REGVIEW_H
#define REGVIEW_H

#include <QWidget>
// TODO: убрать отсюда, заменив на incompelte types
#include <QVector>
#include <QLabel>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QVBoxLayout>

#include "reg.h"
// FOR DEBUG ONLY
#include "regmap.h"

/**
 * @brief The regView_c class
 * Увы, Qt-шные классы не могут быть template'ами. Придется прописывать каждого наследника :(
 */

class regWidget_c : public QWidget
{
    Q_OBJECT

private:
    QVector<QPair<QLabel*, QLineEdit*>> m_qFields;
    QVBoxLayout *m_layout = nullptr;

protected:
    std::unique_ptr<reg_c> m_reg = nullptr;
    virtual void createReg() = 0;
    /**
     * @brief Build
     * Логика построения виджета остается неизменной для любого регистра,
     * т.к. зависит только от абстракции регистра!
     * (в терминах паттерна "фабричный метод" - это Creator)
     */
    void Build() noexcept;

public:
    regWidget_c(QWidget *pwgt = nullptr);
    virtual ~regWidget_c();
};

class dummyReg_c : public regWidget_c
{
    void createReg()
    {
        try {
            std::unique_ptr<reg_c> reg = std::make_unique<regInitControl1_c>();
            m_reg.swap(reg);
        } catch (regExc_c &exc) {
            exc.ToStderr();
        }
    }
public:
    dummyReg_c();
    virtual ~dummyReg_c();
};

#endif // REGVIEW_H
