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
    std::string zipFilePath = (m_outDirPath.back() == '/' || m_outDirPath.back() == '\\') ? m_outDirPath + m_archiveName : m_outDirPath + "/" + m_archiveName;

    int err;
    if ((m_zip = zip_open(zipFilePath.c_str(), ZIP_CREATE | ZIP_EXCL, &err)) == nullptr) {
        zip_error_t error;
        zip_error_init_with_code(&error, err);
        zip_error_fini(&error);

        throw std::runtime_error("Failed to create archive: " + m_archiveName);
    }

    //register callback

    walkDirectory(m_addedDirPath, m_addedDirPath);

    zip_close(m_zip);
}


void Zipper::walkDirectory(const std::string& startdir, const std::string& inputdir)
{
    DIR *dp = ::opendir(m_addedDirPath.c_str());
    if (dp == nullptr) {
        throw std::runtime_error("Failed to open source directory: " + std::string(std::strerror(errno)));
    }

    struct dirent *dirp;
    while ((dirp = readdir(dp)) != nullptr) {
        if (dirp->d_name != std::string(".") && dirp->d_name != std::string("..")) {
            std::string fullname = m_addedDirPath + "/" + dirp->d_name;
            if (isDir(fullname)) {
                if (zip_dir_add(m_zip, fullname.substr(startdir.length() + 1).c_str(), ZIP_FL_ENC_UTF_8) < 0) {
                    throw std::runtime_error("Failed to add directory to zip: " + std::string(zip_strerror(m_zip)));
                }
                walkDirectory(startdir, fullname);
            } else {
                zip_source_t *source = zip_source_file(m_zip, fullname.c_str(), 0, 0);
                if (source == nullptr) {
                    throw std::runtime_error("Failed to add file to zip: " + std::string(zip_strerror(m_zip)));
                }
                if (zip_file_add(m_zip, fullname.substr(startdir.length() + 1).c_str(), source, ZIP_FL_ENC_UTF_8) < 0) {
                    zip_source_free(source);
                    throw std::runtime_error("Failed to add file to zip: " + std::string(zip_strerror(m_zip)));
                }
            }
        }
    }
    ::closedir(dp);
}

void Zipper::saveAt(const std::string& dirPath)
{
    m_outDirPath = dirPath;
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

void Zipper::addDirectory(const std::string& dirName)
{
    m_addedDirPath = dirName;
}
