#pragma once

#include <zip.h>

#include <filesystem>
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
    void walkDirectory();
    void addFile();

    zip_t* m_zip = nullptr;

    std::string m_archiveName = "";
    std::filesystem::directory_entry m_addedDir;
    std::filesystem::directory_entry m_outDir;
};
