#pragma once

#include <zip.h>

#include <functional>
#include <string>

class Zipper
{
public:
    template <typename T>
    std::function<void(const Zipper&,double,T)> onProgress;

    Zipper() = default;

    void setSourceDir(const std::string);
    void setOutDir(const std::string);

    bool addFile();
    bool addDirectory();
    bool save();

private:
    void walkDirectory();

    zip_t& m_zip;
};
