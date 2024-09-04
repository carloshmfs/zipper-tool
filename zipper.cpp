#include <iostream>
#include <stdexcept>
#include <string>

#include <zip.h>

zip_t* create_archive(const std::string& archive_name)
{
    int err;
    zip_t *archive;

    if ((archive = zip_open(archive_name.c_str(), ZIP_CREATE | ZIP_EXCL, &err)) == NULL) {
        zip_error_t error;
        zip_error_init_with_code(&error, err);
        zip_error_fini(&error);

        std::cerr << "DEU ERRO" << std::endl;

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

    std::cout << "break " << std::endl;
}

int main(int argc, char* argv[])
{
    zip_t* file;

    try {
        file = create_archive("test.zip");
        add_file(file, "build/Makefile");
        zip_close(file);
    } catch (const std::runtime_error& e) {
        std::cerr << "ERROR: " << e.what() << std::endl;
        return 1;
    }

    std::cout << "Hello World! aqui" << std::endl;

    return 0;
}
