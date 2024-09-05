#include <ctime>
#include <iostream>
#include <stdexcept>
#include <string>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>

#include <zip.h>

void show_helper(bool is_error = false)
{
    std::string help_msg = "Usage: zipper [path/to/source/dir] [path/to/output/dir]";

    if (is_error) {
        std::cerr << help_msg << std::endl;
        return;
    }

    std::cout << help_msg << std::endl;
}

std::string current_datetime()
{
    auto now = std::chrono::system_clock::now();
    auto in_time_t = std::chrono::system_clock::to_time_t(now);

    std::stringstream ss;
    ss << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d_%H-%M-%S");

    return ss.str();
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
    std::string out_file_name = current_datetime() += ".zip";

    zip_t* file;

    try {
        file = create_archive(out_file_name);
        add_file(file, "build/Makefile");
        zip_close(file);
    } catch (const std::runtime_error& e) {
        std::cerr << "ERROR: " << e.what() << std::endl;
        return 1;
    }

    std::cout << "Backup feito com sucesso." << std::endl;

    return 0;
}
