#pragma once

#include <map>
#include <string>
#include <filesystem>
#include <vector>
#include <optional>
#include <set>
#include <functional>

#include "gaft.hpp"
#include "program_options.hpp"


namespace fs = std::filesystem;


class file_metadata_t
{
    fs::path file_path_;
    uintmax_t file_size_;

    public:
        fs::path file_path() { return file_path_; };
        void file_path(fs::path f_path) { file_path_ = f_path; };

        uintmax_t file_size() { return file_size_; };
        void file_size(uintmax_t file_size) { file_size_ = file_size; };

        const std::string file_name() { return file_path_.filename(); };
};

struct path_preprocess_info_t
{
    bool path_exists { false };
    bool is_dir { false };
    bool is_processable() { return path_exists && is_dir; }
};

using file_filter_func = std::function<bool(const fs::path&)>;
using file_ext_filter_func = file_filter_func;


class metadata_processor_t
{
    public:
        metadata_processor_t();
        ~metadata_processor_t();

        path_preprocess_info_t preprocess_info         (const fs::path& dir_path);

        std::optional<std::vector<file_metadata_t>>
        get_recursive_file_metadata                    (const fs::path& dir_path, file_search_opts_t opts);

    private:
        bool path_exists     (const fs::path& path);
        bool is_dir          (const fs::path& dir_path);
        bool is_processable  (const fs::path& f_path);
        bool should_process  (const fs::path& f_path, file_search_opts_t opts);

        file_metadata_t get_metadata      (const fs::path& f_path);
        uintmax_t       compute_file_size (const fs::path& f_path);
};

