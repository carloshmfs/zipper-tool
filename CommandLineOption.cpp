#include "CommandLineOption.h"

#include <string>

CommandLineOption CommandLineOption::setDescription(const std::string& description)
{
    m_description = description;
    return *this;
}

CommandLineOption CommandLineOption::setValueName(const std::string& valueName)
{
    m_valueName = valueName;
    return *this;
}

CommandLineOption CommandLineOption::setDefaultValue(const std::string& defaultValue)
{
    m_defaultValue = defaultValue;
    return *this;
}
