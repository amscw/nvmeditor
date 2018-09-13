#ifndef REG_H
#define REG_H

#include <vector>
#include <map>
#include "exc.h"

struct regExc_c : public exc_c
{
    enum class errCode_t : std::uint32_t {
        ERR_OPENFILE,
        ERR_PARSE,
        ERR_NOREGSFOUND,
        ERR_INVALIDOFFSET
    } m_errCode;

    regExc_c(enum errCode_t code, const std::string &strFile, const std::string &strFunction, const std::string &strWhat = "") noexcept :
        exc_c(strFile, strFunction, strWhat), m_errCode(code)
    {}

    const std::string &Msg() const noexcept override { return strErrorMessages[static_cast<int>(m_errCode)]; }
    void ToStderr() const noexcept override
    {
        std::cerr << "WTF:" << m_strFile << "(" << m_strFunction << "):" << strErrorMessages[static_cast<int>(m_errCode)] << "-" << m_strWhat<< std::endl;
    }

private:
    static std::string strErrorMessages[];
};

/**
 * @brief The reg_c class абстракция (Product) регистра NVM-образа.
 * Размер регистра не может быть менее 1 word, если это положение нарушается, регистр становится комбинированным.
 * Субклассы (ConcreteProduct) задают: адрес, имя, размер регистра в словах, а также определяют собственные наборы полей и мапперы.
 *
 * В создателе (Creator) определена логика построения представления (view) абстрактного регистра.
 * Конкретные создатели (ConcreteCreator) реализуют фабричный метод конкретного регистра.
 * При необходимости создатели могут декорировать логику суперкласса.
 *
 * TODO: в идеале конкретные продукты сделать template'ами, чтобы не пришлось вручную писать код под каждый регистр.
 * Но это пока не представляется возможным, т.к. рефлексия времени компиляции не позволяет извлекать имена полей структур :(
 *
 * TODO: выключить упорядочивание m_mapFields
 */
class reg_c
{
    static std::vector<std::uint16_t> raw;

protected:
    const std::string m_strRegName;
    const int m_nWord, m_nCount;
    const std::vector<std::uint16_t>::iterator m_itBase, m_itEnd;

    std::map<std::string, std::uint16_t> m_mapFields;

    virtual void dumpWords() const noexcept;

public:
    static std::size_t LoadNVMImage(const std::string &strFilename);
    reg_c(const std::string &strName, int word, int count);
};

/**
 * @brief The regViewer_c class декоратор для reg_c::dumpWords
 * Позволяет просматривать все поля регистра
 */
class regViewer_c : public reg_c
{
protected:
    virtual void dumpWords() const noexcept;

public:
    regViewer_c(const std::string &strName, int word, int count) : reg_c(strName, word, count){}
    virtual ~regViewer_c(){}
};


#endif // REG_H
