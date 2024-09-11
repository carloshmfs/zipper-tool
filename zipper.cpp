#include "ProgressBar.h"

#include <ctime>
#include <iostream>
#include <stdexcept>
#include <string>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <vector>
#include <algorithm>
#include <ctype.h>
#include <dirent.h>
#include <sys/stat.h>
#include <errno.h>
#include <cstring>

#include <zip.h>

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

zip_t* create_archive(const std::string& archive_name)
{
    int err;
    zip_t *archive;

    if ((archive = zip_open(archive_name.c_str(), ZIP_CREATE | ZIP_EXCL, &err)) == NULL) {
        zip_error_t error;
        zip_error_init_with_code(&error, err);
        zip_error_fini(&error);

        throw std::runtime_error("Failed to create archive: " + archive_name);
    }

    return archive;
}

void add_file(zip_t* archive, const std::string& source_path)
{
    zip_source_t* source = zip_source_file(archive, source_path.c_str(), 0, 0);

    if (source == nullptr) {
        throw std::runtime_error("Failed to open source file.");
    }

    if ( zip_file_add(archive, source_path.c_str(), source, ZIP_FL_ENC_UTF_8) < 0 ) {
        zip_source_free(source);
        throw std::runtime_error("Failed to add file to archive.");
    }
}

void walk_directory(zip_t* archive, const std::string& startdir, const std::string& inputdir)
{
    DIR *dp = ::opendir(inputdir.c_str());
    if (dp == nullptr) {
        throw std::runtime_error("Failed to open input directory: " + std::string(std::strerror(errno)));
    }

    struct dirent *dirp;
    while ((dirp = readdir(dp)) != NULL) {
        if (dirp->d_name != std::string(".") && dirp->d_name != std::string("..")) {
            std::string fullname = inputdir + "/" + dirp->d_name;
            if (is_dir(fullname)) {
                if (zip_dir_add(archive, fullname.substr(startdir.length() + 1).c_str(), ZIP_FL_ENC_UTF_8) < 0) {
                    throw std::runtime_error("Failed to add directory to zip: " + std::string(zip_strerror(archive)));
                }
                walk_directory(archive, startdir, fullname);
            } else {
                zip_source_t *source = zip_source_file(archive, fullname.c_str(), 0, 0);
                if (source == nullptr) {
                    throw std::runtime_error("Failed to add file to zip: " + std::string(zip_strerror(archive)));
                }
                if (zip_file_add(archive, fullname.substr(startdir.length() + 1).c_str(), source, ZIP_FL_ENC_UTF_8) < 0) {
                    zip_source_free(source);
                    throw std::runtime_error("Failed to add file to zip: " + std::string(zip_strerror(archive)));
                }
            }
        }
    }
    ::closedir(dp);
}

void on_progress_state_change(zip_t* archive, double progress, void* user_data)
{
    ProgressBar* bar = reinterpret_cast<ProgressBar*>(user_data);
    bar->update(progress * 100);
    bar->show();
}

int main(int argc, char* argv[])
{
    if (argc < 2) {
        std::cerr << "ERROR: no source directory provided." << std::endl;
        show_helper(true);
        return 1;
    }

    if (argc < 3) {
        std::cerr << "ERROR: no output directory provided." << std::endl;
        show_helper(true);
        return 1;
    }

    std::string source_dir = argv[1];
    std::string out_dir = argv[2];

    std::string source_dir_name = get_last_dir(source_dir);
    std::string out_file_name = create_slug(source_dir_name) + "_" + current_datetime() += ".zip";

    zip_t* file;
    file = create_archive(out_dir + "/" + out_file_name);

    ProgressBar bar;
    zip_register_progress_callback_with_state(file, 0.02, on_progress_state_change, nullptr, &bar);

    try {

        walk_directory(file, source_dir, source_dir);

    } catch (const std::runtime_error& e) {
        zip_close(file);
        std::cerr << "ERROR: " << e.what() << std::endl;
        return 1;
    }

    zip_close(file);

    std::cout << std::endl << "Zip archive done successfully." << std::endl;

    return 0;
}
