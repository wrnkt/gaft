#include "metadata_processor.hpp"
#include "gaft.hpp"

#include <string>
#include <iostream>
#include <filesystem>
#include <vector>
#include <algorithm>
#include <iterator>


metadata_processor_t::metadata_processor_t() {}
metadata_processor_t::~metadata_processor_t() {}


bool metadata_processor_t::add_file_search_ext(GAFT_F_EXT ext)
{
    auto [it, success] = file_search_exts.insert(ext);
    return success;
}

bool metadata_processor_t::remove_file_search_ext(GAFT_F_EXT ext)
{
    return file_search_exts.erase(ext);
}


bool metadata_processor_t::add_file_search_kind(GAFT_F_KIND kind)
{
    auto [it, success] = file_search_kinds.insert(kind);
    return success;
}

bool metadata_processor_t::remove_file_search_kind(GAFT_F_KIND kind)
{
    return file_search_kinds.erase(kind);
}


bool metadata_processor_t::should_process(const fs::path& f_path)
{
    const auto& [ext, kind] = FILE_CLASSIFICATION_MAP.at(f_path.extension());
    if(file_search_exts.contains(ext) || file_search_kinds.contains(kind)) return true;
    return false;
}

bool metadata_processor_t::is_processable(const fs::path& f_path)
{
    return fs::is_regular_file(f_path) && fs::exists(f_path);
}


path_preprocess_info_t metadata_processor_t::preprocess_info(const fs::path& dir_path)
{
    return path_preprocess_info_t {
        .path_exists = path_exists(dir_path),
        .is_dir = is_dir(dir_path)
    };
}

bool metadata_processor_t::path_exists(const fs::path& path)
{
    return fs::exists(path);
}

bool metadata_processor_t::is_dir(const fs::path& dir_path)
{
    return fs::is_directory(dir_path);
}


std::vector<file_metadata_t> metadata_processor_t::get_recursive_file_metadata(const fs::path& dir_path)
{
    std::vector<file_metadata_t> fm_vec {};
    for(fs::path f_path : fs::recursive_directory_iterator(dir_path)) {
        if(is_processable(f_path) && should_process(f_path)) {
            fm_vec.push_back(get_metadata(f_path));
        }
    }
    return fm_vec;
}

file_metadata_t metadata_processor_t::get_metadata(const fs::path& f_path)
{
    file_metadata_t fm {};
    if(f_path.has_filename()) {
        fm.file_name = f_path.filename();
    }
    return fm;
}

uintmax_t metadata_processor_t::compute_file_size(const fs::path& f_path)
{
    auto err = std::error_code {};
    auto filesize = fs::file_size(f_path, err);
    if (filesize != static_cast<uintmax_t>(-1)) {
        return filesize;
    }
    return static_cast<uintmax_t>(-1);
}
