#pragma once

#include <string>
#include <filesystem>
#include <vector>

struct file_metadata_t {
    std::filesystem::path file_path;
    std::string file_name;
    uintmax_t file_size;
};

struct dir_process_result_t {
    bool path_exists { false };
    bool is_dir { false };
    bool is_valid() {
        return path_exists && is_dir;
    }
};

class metadata_processor_t {
    public:
        std::vector<file_metadata_t> get_recursive_file_metadata(const std::filesystem::path& dir_path);
        dir_process_result_t confirm_for_processing(const std::filesystem::path& p);
    private:
        uintmax_t compute_file_size(const std::filesystem::path& p);
        bool get_metadata(const std::filesystem::path& file_path, file_metadata_t* const fm);
        bool path_exists(const std::filesystem::path& p);
        bool is_dir(const std::filesystem::path& p);
};

