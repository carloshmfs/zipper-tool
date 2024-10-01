#pragma once

class ArgsParser
{
public:
    ArgsParser(int argc, char* argv[])
        : m_raw_argc(argc)
        , m_raw_argv(argv)
    {}

    void parse();

private:
    int m_raw_argc;
    char** m_raw_argv;
};
