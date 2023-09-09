#pragma once

#include <string>
#include <filesystem>
#include <vector>

namespace fs = std::filesystem;

struct file_metadata_t {
    fs::path file_path;
    std::string file_name;
    uintmax_t file_size;
};

struct path_preprocess_info_t {
    bool path_exists { false };
    bool is_dir { false };
    bool is_processable() {
        return path_exists && is_dir;
    }
};

class metadata_processor_t {
    public:
        path_preprocess_info_t preprocess_info(const fs::path& p);
        std::vector<file_metadata_t> get_recursive_file_metadata(const fs::path& dir_path);

    private:
        bool valid_file(const fs::path& f_path);

        bool path_exists(const fs::path& p);
        bool is_dir(const fs::path& p);

        bool get_metadata(const fs::path& file_path, file_metadata_t* const fm);
        uintmax_t compute_file_size(const fs::path& p);
};

