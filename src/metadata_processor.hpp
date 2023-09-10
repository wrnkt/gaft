#pragma once

#include <map>
#include <string>
#include <filesystem>
#include <vector>
#include <set>
#include <functional>

#include "gaft.hpp"


namespace fs = std::filesystem;


struct file_metadata_t
{
    fs::path file_path;
    std::string file_name;
    uintmax_t file_size;
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

        path_preprocess_info_t preprocess_info (const fs::path& dir_path);

        std::vector<file_metadata_t> get_recursive_file_metadata (const fs::path& dir_path);

        bool add_file_search_ext     (GAFT_F_EXT ext);
        bool remove_file_search_ext  (GAFT_F_EXT ext);

        bool add_file_search_kind    (GAFT_F_KIND kind);
        bool remove_file_search_kind (GAFT_F_KIND kind);

    private:

        std::set<GAFT_F_EXT>  file_search_exts {};
        std::set<GAFT_F_KIND> file_search_kinds {};

        bool path_exists     (const fs::path& path);
        bool is_dir          (const fs::path& dir_path);
        bool is_processable  (const fs::path& f_path);
        bool should_process  (const fs::path& f_path);


        file_metadata_t get_metadata      (const fs::path& f_path);
        uintmax_t       compute_file_size (const fs::path& f_path);

};

