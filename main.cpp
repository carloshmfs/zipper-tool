#include "Zipper.h"
#include "ProgressBar.h"
#include "utils.h"

#if 0
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
#endif

int main(int argc, char* argv[])
{
    Zipper zipper;
    zipper.archiveName("test.zip");
    zipper.saveAt("test");
    zipper.addDirectory("build");
    zipper.make();

    return 0;
}
