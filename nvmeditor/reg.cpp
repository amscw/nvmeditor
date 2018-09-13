#include "reg.h"
#include <fstream>
#include <regex>

//-----------------------------------------------------------------------------
// variables
//-----------------------------------------------------------------------------

std::string regExc_c::strErrorMessages[] = {
    "cannot open file",
    "parsing error",
    "no registers found"
};

std::vector<std::uint16_t> reg_c::raw;

//-----------------------------------------------------------------------------
// functions
//-----------------------------------------------------------------------------

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
            throw (regExc_c(regExc_c::errCode_t::ERR_OPENFILE, __FILE__, __FUNCTION__, strFilename));
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
    m_strRegName(strName), m_nWord(word), m_nCount(count), m_itBase(raw.begin() + m_nWord), m_itEnd(raw.begin() + m_nWord + m_nCount)
{

}

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

void regViewer_c::dumpWords() const noexcept
{
    std::ostringstream oss;

    reg_c::dumpWords();
    oss << std::endl << std::hex;
    for (auto &f : m_mapFields)
        oss << f.first << "=0x" << f.second << ";" << std::endl;
    TRACE_BY_STREAM(oss);
}
