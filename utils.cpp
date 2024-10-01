#include "utils.h"

#include <iostream>
#include <string>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <vector>
#include <algorithm>
#include <ctype.h>
#include <sys/stat.h>

void show_helper(bool is_error = false)
{
    std::string help_msg = "Usage: archive <path/to/source/dir> <path/to/output/dir>";

    if (is_error) {
        std::cerr << help_msg << std::endl;
        return;
    }

    std::cout << help_msg << std::endl;
}

bool is_dir(const std::string& dir)
{
    struct stat st;
    ::stat(dir.c_str(), &st);
    return S_ISDIR(st.st_mode);
}

std::string current_datetime()
{
    auto now = std::chrono::system_clock::now();
    auto in_time_t = std::chrono::system_clock::to_time_t(now);

    std::stringstream ss;
    ss << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d_%H-%M-%S");

    return ss.str();
}

std::string get_last_dir(const std::string& path)
{
    std::stringstream ss(path);

    std::string token;
    std::vector<std::string> tokens;
    while (std::getline(ss, token, '\\')) {
        tokens.push_back(token);
    }

    if (!tokens.empty()) {
        return tokens.back();
    }

    return "\\";
}

bool is_url_friendly(char ch)
{
    return std::isalnum(ch) || ch == '-';
}

std::string create_slug(const std::string& input)
{
    std::string slug = input;

    // Convert all characters to lowercase
    std::transform(slug.begin(), slug.end(), slug.begin(), ::tolower);

    // Replace spaces with hyphens
    std::replace(slug.begin(), slug.end(), ' ', '-');

    // Remove non-alphanumeric characters except hyphens
    slug.erase(std::remove_if(slug.begin(), slug.end(), [](char ch) {
        return !is_url_friendly(ch);
    }), slug.end());

    // Remove consecutive hyphens
    auto new_end = std::unique(slug.begin(), slug.end(), [](char a, char b) {
        return a == '-' && b == '-';
    });
    slug.erase(new_end, slug.end());

    // Remove leading or trailing hyphens
    if (!slug.empty() && slug.front() == '-') {
        slug.erase(slug.begin());
    }
    if (!slug.empty() && slug.back() == '-') {
        slug.erase(slug.end() - 1);
    }

    return slug;
}
