#include "Zipper.h"
#include "utils.h"

#include <zip.h>

#include <iostream>
#include <iterator>
#include <filesystem>
#include <stdexcept>
#include <dirent.h>
#include <errno.h>
#include <cstring>
#include <string>

void Zipper::make()
{
    std::string zipFilePath = (m_outDir.path().string().back() == '/' || m_outDir.path().string().back() == '\\') ? m_outDir.path().string() + m_archiveName : m_outDir.path().string() + "/" + m_archiveName;

    int err;
    if ((m_zip = zip_open(zipFilePath.c_str(), ZIP_CREATE | ZIP_EXCL, &err)) == nullptr) {
        zip_error_t error;
        zip_error_init_with_code(&error, err);
        zip_error_fini(&error);

        throw std::runtime_error("Failed to create archive: " + m_archiveName);
    }

    //register callback

    walkDirectory();

    zip_close(m_zip);
}


void Zipper::walkDirectory()
{
    auto dirIter = std::filesystem::recursive_directory_iterator(m_addedDir.path());
    for (const auto& file : dirIter) {
        std::cout << dirIter.depth() << " " << file.relative_path().string() << std::endl; 
    }
}

void Zipper::saveAt(const std::string& dirPath)
{
    m_outDir = std::filesystem::directory_entry(dirPath);
}

void Zipper::archiveName(const std::string& name)
{
    m_archiveName = name;
}

void Zipper::archiveNameFromDirectory(const std::string& dirPath)
{
    std::filesystem::path outputPath(dirPath);
    std::string outputDirName = std::prev(outputPath.end())->string();
    outputDirName = toSlug(outputDirName) + "_" + currentDatetime() + ".zip";

    archiveName(outputDirName);
}

void Zipper::addDirectory(const std::string& dirPath)
{
    m_addedDir = std::filesystem::directory_entry(dirPath);
}
