#include "CommandLineParser.h"

#include <iostream>
#include <string>

int CommandLineParser::showHelp(int statusCode) const
{
    std::cout << "Usage: " << m_applicationName;

    for (const auto& arg : m_positionalArguments) {
        std::cout << " " << arg.getSyntax();
    }
    std::cout << std::endl;

    return statusCode;
}

void CommandLineParser::setApplicationName(const std::string& name)
{
    m_applicationName = name;
}

void CommandLineParser::setApplicationDescription(const std::string& description)
{
    m_applicationDescription = description;
}

void CommandLineParser::addPositionalArgument(const std::string& name, const std::string& description, const std::string& syntax, const std::string& defaultValue)
{
    m_positionalArguments.emplace_back(CommandLineArgument(name, description, syntax, defaultValue));
}

void CommandLineParser::parse()
{
    parsePositionalArguments();
    parseOptions();
}

void CommandLineParser::parsePositionalArguments()
{
    for (auto& arg : m_positionalArguments) {
        if (m_argumentIndex > m_argc) {
            break;
        }

        char* foundAppArgument = m_argv[m_argumentIndex];
        if (foundAppArgument != nullptr) {
            arg.setValue(foundAppArgument);
        }

        m_argumentIndex++;
    }
}

void CommandLineParser::parseOptions()
{
    // TODO...
}

bool CommandLineParser::isSet(const std::string& value) const
{
    return false;
}

std::string CommandLineParser::getValue(const std::string& value) const
{
    return std::string();
}
