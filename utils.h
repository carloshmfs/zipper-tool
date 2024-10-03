#pragma once

#include <string>

bool isDir(const std::string& dir);
bool isUrlFriendly(char ch);

std::string currentDatetime();
std::string getLastDir(const std::string& path);
std::string toSlug(const std::string& input);
