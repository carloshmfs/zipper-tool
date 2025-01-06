#include "Zipper.h"
#include "utils.h"

#include <zip.h>

#include <bits/stdc++.h>
#include <cstring>
#include <dirent.h>
#include <filesystem>
#include <iterator>
#include <print>
#include <stdexcept>
#include <string>

void Zipper::make()
{
    std::string zipFilePath = (m_outDir.path().string().back() == '/' || m_outDir.path().string().back() == '\\')
        ? m_outDir.path().string() + m_archiveName
        : m_outDir.path().string() + "/" + m_archiveName;

    int err;
    if ((m_zip = zip_open(zipFilePath.c_str(), ZIP_CREATE | ZIP_EXCL, &err)) == nullptr) {
        zip_error_t error;
        zip_error_init_with_code(&error, err);
        zip_error_fini(&error);

        throw std::runtime_error("Failed to create archive: " + m_archiveName);
    }

    walkDirectory();

    zip_close(m_zip);
}

void Zipper::walkDirectory()
{
    auto handlePath = [&](const std::filesystem::path& full_path) -> void {
        // size() + 1 so it removes the slash from the beggin of the path
        std::string relative_path = full_path.string().replace(0, m_addedDir.path().string().size() + 1, "");

        if (std::filesystem::is_directory(full_path)) {
            zip_dir_add(m_zip, relative_path.c_str(), ZIP_FL_ENC_GUESS);
            return;
        }

        zip_source_t* source = zip_source_file(m_zip, full_path.string().c_str(), 0, 0);
        zip_file_add(m_zip, relative_path.c_str(), source, ZIP_FL_ENC_GUESS);
    };

    auto dirIter = std::filesystem::recursive_directory_iterator(m_addedDir.path());
    for (const auto& file : dirIter) {
        handlePath(file);
    }
}

void Zipper::saveAt(const std::string& dirPath) { m_outDir = std::filesystem::directory_entry(dirPath); }

void Zipper::archiveName(const std::string& name) { m_archiveName = name; }

void Zipper::archiveNameFromDirectory(const std::string& dirPath)
{
    std::filesystem::path outputPath(dirPath);
    std::string outputDirName = std::prev(outputPath.end())->string();
    outputDirName = toSlug(outputDirName) + "_" + currentDatetime() + ".zip";

    archiveName(outputDirName);
}

void Zipper::addDirectory(const std::string& dirPath) { m_addedDir = std::filesystem::directory_entry(dirPath); }
