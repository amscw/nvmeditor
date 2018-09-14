#include "reg.h"
#include <fstream>
#include <regex>
#include <algorithm>

//-----------------------------------------------------------------------------
// variables
//-----------------------------------------------------------------------------

std::string regExc_c::strErrorMessages[] = {
    "cannot open file",
    "parsing error",
    "NVM image is not loaded or empty"
    "register not found"
};

std::vector<std::uint16_t> reg_c::raw;

//-----------------------------------------------------------------------------
// functions
//-----------------------------------------------------------------------------

regExc_c::regExc_c(enum errCode_t code, const std::string &strFile, const std::string &strFunction, const std::string &strWhat) noexcept :
    exc_c(strFile, strFunction, strWhat), m_errCode(code)
{}

std::size_t reg_c::LoadNVMImage(const std::string &strFilename)
{
    std::ostringstream oss;
    std::ifstream ifs;

    // all exceptions are enabled
    ifs.exceptions(std::ios_base::failbit | std::ios_base::eofbit | std::ios_base::badbit);
    try
    {
        ifs.open(strFilename, std::ios_base::binary);   // TODO: any exceptions here?
        if (ifs.is_open())
        {
            for(std::string str;;)
            {
                // get line
                ifs.get(*oss.rdbuf());
                str = std::move(oss.str());

                // parse line
                std::smatch sm;
                while(std::regex_search(str, sm, std::regex{"[0-9a-fA-F]+"}))
                {
                    // std::cout << sm.str() << std::endl;
                    raw.push_back(static_cast<std::uint16_t>(std::stoul(sm.str(), nullptr, 16)));
                    str = sm.suffix();
                }

                // do next
                oss.str("");
                oss.clear();
                ifs.seekg(1, std::ios_base::cur);	// ignore '\n' symbol
            }
        } else {
            throw (regExc_c(regExc_c::errCode_t::ERR_OPEN_FILE, __FILE__, __FUNCTION__, strFilename));
        }
    } catch (const /* std::ios_base::failure */ std::exception &e) {
        oss << e.what() << "(" << std::boolalpha << "fail=" << ifs.fail() << ", eof=" << ifs.eof() << ", bad=" << ifs.bad() << ")";
        TRACE_BY_STREAM(oss);
    }
    oss << "found: " << raw.size() << " words";
    TRACE_BY_STREAM(oss);
    return raw.size();
}

reg_c::reg_c(const std::string &strName, int word, int count) :
    m_strRegName(strName), m_nWord(word), m_nCount(count), m_itBase(raw.begin() + m_nWord), m_itEnd(m_itBase + m_nCount)
{
    if (raw.size() == 0)
        throw regExc_c(regExc_c::errCode_t::ERR_NO_IMAGE, __FILE__, __FUNCTION__);
}

reg_c::~reg_c(){}

void reg_c::dumpWords() const noexcept
{
    std::ostringstream oss;

    oss << m_strRegName << "={";
    for (auto it = m_itBase; it < m_itEnd; it++)
    {
        oss << "0x" << std::hex << std::setw(4) << std::setfill('0') << *it;
        oss.clear();
        oss << ", ";
    }
    oss << "}";
    TRACE_BY_STREAM(oss);
}

std::uint16_t reg_c::GetFieldValue(const std::string &strFieldname)
{
    listIterator_t it = std::find_if(m_listFields.begin(), m_listFields.end(), IsMatchField(strFieldname));
    if (it == m_listFields.end())
        throw regExc_c(regExc_c::errCode_t::ERR_REGFIELD_NOT_FOUND, __FILE__, __FUNCTION__, strFieldname);
    return (*it).second;
}

void regViewer_c::dumpWords() const noexcept
{
    std::ostringstream oss;

    reg_c::dumpWords();
    oss << std::endl << std::hex;
    for (auto &f : m_listFields)
        oss << f.first << "=0x" << f.second << ";" << std::endl;
    TRACE_BY_STREAM(oss);
}
