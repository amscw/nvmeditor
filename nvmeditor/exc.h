#ifndef EXC_H
#define EXC_H

#include "tracers.hpp"

struct exc_c /* : public std::exception */
{
    const std::string m_strFile;
    const std::string m_strFunction;
    const std::string m_strWhat;

    exc_c(const std::string &strFile, const std::string &strFunction, const std::string &strWhat = "") noexcept :
        m_strFile(strFile), m_strFunction(strFunction), m_strWhat(strWhat)
    {}
    virtual ~exc_c() {}

    inline const std::string &What() const noexcept { return m_strWhat; }
    virtual const std::string &Msg() const noexcept = 0;
    virtual void ToStderr() const noexcept = 0;
};

#endif // EXC_H
