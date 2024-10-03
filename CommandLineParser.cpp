#include "CommandLineParser.h"

#include <iostream>
#include <string>
#include <utility>

int CommandLineParser::showHelp(int statusCode) const
{
    std::cout << "USAGE: " << m_applicationName;

    if (! m_positionalArguments.empty()) {
        for (const auto& arg : m_positionalArguments) {
            std::cout << " " << arg.getSyntax();
        }
    }

    std::cout << std::endl << std::endl << m_applicationDescription << std::endl;

    if (! m_positionalArguments.empty()) {
        std::cout << std::endl << std::endl << "ARGUMENTS:" << std::endl;

        for (const auto& arg : m_positionalArguments) {
            std::cout << " " << arg.getValueName() << "\t\t" << arg.getDescription() << std::endl;
        }
    }

    if (! m_options.empty()) {
        // TODO...
        std::unreachable();
    }

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
    for(const auto& positionalArgument  : m_positionalArguments) {
        if (value == positionalArgument.getValueName() && !positionalArgument.getValue().empty()) {
            return true;
        }
    }

    return false;
}

std::string CommandLineParser::getValue(const std::string& value) const
{
    for(const auto& positionalArgument  : m_positionalArguments) {
        if (value == positionalArgument.getValueName()) {
            return positionalArgument.getValue();
        }
    }

    return std::string();
}
