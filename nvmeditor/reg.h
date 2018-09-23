#ifndef REG_H
#define REG_H

#include <vector>
#include <list>
#include <memory>
#include "exc.h"

struct regExc_c : public exc_c
{
    enum class errCode_t : std::uint32_t {
        ERR_OPEN_FILE,
        ERR_SAVE_FILE,
        ERR_PARSE,
        ERR_NO_IMAGE,
        ERR_REGFIELD_NOT_FOUND,
        ERR_OUT_OF_RANGE,
    } m_errCode;

    regExc_c(enum errCode_t code, const std::string &strFile, const std::string &strFunction, const std::string &strWhat = "") noexcept;

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
 */
class reg_c
{
    static std::vector<std::uint16_t> raw;
    static std::string filename;

protected:
    using item_t = std::pair<std::string, std::uint16_t>;
    using list_t = std::list<item_t>;
    using listIterator_t = list_t::iterator;

    struct IsMatchField : public std::unary_function<item_t, bool>
    {
        IsMatchField(const std::string &fieldName) noexcept : m_strFieldName(fieldName)  {}
        bool operator()(const item_t& nextField) const noexcept { return m_strFieldName == nextField.first; }
    private:
        const std::string m_strFieldName;
    };

    const std::string m_strRegName;
    const int m_nWord, m_nCount;
    const std::vector<std::uint16_t>::iterator m_itBase, m_itEnd;

    list_t m_listFields;

    virtual void dumpWords() const noexcept;
    std::uint16_t getFieldValue(const std::string &strFieldname);

public:
    static std::size_t LoadNVMImage(const std::string &strFilename);
    static void SaveNVMImage(const std::string &strFilename = filename);

    reg_c(const std::string &strName, int word, int count);
    virtual ~reg_c();

    const std::string &Name() const noexcept {return m_strRegName; }
    const std::string &GetFilename() const noexcept { return filename; }
    virtual void ToDefault() noexcept = 0;
    virtual void Save() noexcept = 0;
    std::size_t GetFieldsCount() const noexcept { return m_listFields.size(); }
    item_t &operator[](int i);

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
