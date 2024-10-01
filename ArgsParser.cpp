#include "ArgsParser.h"

#include <iostream>
#include <string>

void ArgsParser::addPositionalArgument(const std::string& argument, const std::string& name, const std::string& description)
{
    m_registered_args.push_back({
        .name = name,
        .description = description,
        .value = argument
    });
}

void ArgsParser::parse() const
{
    for (int i = 0; i < m_registered_args.size(); i++) {
        m_registered_args[i].value = "aosihfoaisf";
    }
}

bool ArgsParser::checkIfArgExists(const std::string& arg) const
{
    for (const auto& user_arg : m_user_args) {
        if (arg == user_arg) {
            return true;
        }
    }

    return false;
}
