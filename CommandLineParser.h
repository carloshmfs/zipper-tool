#pragma once

#include "CommandLineOption.h"
#include "CommandLineArgument.h"
#include <string>
#include <vector>

class CommandLineParser
{
public:
    explicit CommandLineParser(int argc, char* argv[])
        : m_argc(argc)
        , m_argv(argv)
        , m_applicationName("")
        , m_applicationDescription("")
        , m_argumentIndex(1)
    {}

    void setApplicationName(const std::string& name);
    void setApplicationDescription(const std::string& description);
    
    void addOption(const std::string& name, const std::string& description, const std::string& syntax);
    void addOption(const CommandLineOption& argument);
    std::vector<CommandLineOption> options() const;

    void addPositionalArgument(const std::string& name, const std::string& description, const std::string& syntax, const std::string& defaultValue = "");
    void addPositionalArgument(const CommandLineArgument& argument);
    std::vector<CommandLineOption> positionalArguments() const;

    bool isSet(const std::string& value) const;
    std::string getValue(const std::string& value) const;

    int showHelp(int exitCode = 0) const;

    void parse();

private:
    const char* findApplicationArgument(const std::string& argument) const;

    void parsePositionalArguments();
    void parseOptions();

    std::vector<CommandLineOption> m_options;
    std::vector<CommandLineArgument> m_positionalArguments;

    std::string m_applicationName;
    std::string m_applicationDescription;

    int m_argumentIndex;
    int m_argc;
    char** m_argv;
};
