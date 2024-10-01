#pragma once

#include <string>
#include <vector>

struct Argument {
    std::string name;
    std::string description;

    const std::string& refValue;

    void operator=(const std::string& value) { value = refValue; }
};

struct Option {
    std::string short_name;
    std::string long_name;

    bool isRequired = false;
};

class ArgsParser
{
public:
    ArgsParser(int argc, char* argv[])
        : m_raw_argc(argc)
        , m_raw_argv(argv)
    {
        for (int i = 1; i < argc; i++) {
            m_user_args.push_back(argv[i]);
        }
    }

    void addPositionalArgument(const std::string& argument, const std::string& name, const std::string& description);

    void parse() const;

private:
    bool checkIfArgExists(const std::string& arg) const;

    std::vector<Argument> m_registered_args;
    std::vector<Option> m_registered_options;

    std::vector<std::string> m_user_args;

    int m_raw_argc;
    char** m_raw_argv;
};
