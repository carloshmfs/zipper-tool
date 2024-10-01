#pragma once

#include <string>

void show_helper(bool is_error);

bool is_dir(const std::string& dir);

bool is_url_friendly(char ch);

std::string current_datetime();

std::string get_last_dir(const std::string& path);

std::string create_slug(const std::string& input);
