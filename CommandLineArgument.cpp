#include "CommandLineArgument.h"

CommandLineArgument CommandLineArgument::setValueName(const std::string& valueName)
{
    return *this;
}

std::string CommandLineArgument::getValueName() const
{
    return m_valueName;
}

CommandLineArgument CommandLineArgument::setDescription(const std::string& description)
{
    return *this;
}

std::string CommandLineArgument::getDescription() const
{
    return m_description;
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

std::string CommandLineArgument::getValue() const
{
    return m_value;
}
