#pragma once

#include <string>

class CommandLineArgument
{
public:
    CommandLineArgument() = default;
    explicit CommandLineArgument(const std::string& valueName, const std::string& description, const std::string& syntax, const std::string& defaultValue)
        : m_valueName(valueName)
        , m_description(description)
        , m_defaultValue(defaultValue)
        , m_syntax(syntax)
    {}

    CommandLineArgument setValueName(const std::string& valueName);
    std::string getValueName() const;

    CommandLineArgument setDescription(const std::string& description);
    std::string getDescription() const;

    CommandLineArgument setDefaultValue(const std::string& value);
    std::string getDefaultValue() const;

    CommandLineArgument setSyntax(const std::string& syntax);
    std::string getSyntax() const;

    void setValue(const std::string& value);
    std::string getValue() const;

private:
    std::string m_description;
    std::string m_valueName;
    std::string m_defaultValue;
    std::string m_syntax;

    std::string m_value;
};
