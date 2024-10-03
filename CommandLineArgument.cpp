#include "CommandLineArgument.h"

CommandLineArgument CommandLineArgument::setValueName(const std::string& valueName)
{
    return *this;
}

CommandLineArgument CommandLineArgument::setDescription(const std::string& description)
{
    return *this;
}

CommandLineArgument CommandLineArgument::setDefaultValue(const std::string& value)
{
    return *this;
}

CommandLineArgument CommandLineArgument::setSyntax(const std::string& syntax)
{
    return *this;
}

std::string CommandLineArgument::getSyntax() const
{
    return m_syntax;
}

void CommandLineArgument::setValue(const std::string& value)
{
    m_value = value;
}
