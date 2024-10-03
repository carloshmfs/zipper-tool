#pragma once

#include <string>

class CommandLineOption
{
public:
    explicit CommandLineOption(const std::string& name) 
        : m_name(name)
    {}

    CommandLineOption setDescription(const std::string& description);
    CommandLineOption setValueName(const std::string& valueName);
    CommandLineOption setDefaultValue(const std::string& valueName);

private:
    const std::string& m_name;
    std::string m_description;
    std::string m_valueName;
    std::string m_defaultValue;
};
