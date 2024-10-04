#pragma once

#include <zip.h>

#include <functional>
#include <string>

class Zipper
{
public:
    // template <typename T>
    // std::function<void(const Zipper&,double,T)> onProgress;

    void saveAt(const std::string& dirPath);
    void archiveName(const std::string& name);
    void archiveNameFromDirectory(const std::string& dirPath);

    void addDirectory(const std::string& dirPath);
    void make();

private:
    void walkDirectory(const std::string& startdir, const std::string& inputdir);
    void addFile();

    zip_t* m_zip = nullptr;

    std::string m_archiveName = "";
    std::string m_addedDirPath = "";
    std::string m_outDirPath = "";
};
